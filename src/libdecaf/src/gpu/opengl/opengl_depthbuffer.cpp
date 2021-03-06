#include "opengl_driver.h"
#include <glbinding/gl/gl.h>

namespace gpu
{

namespace opengl
{

bool GLDriver::checkActiveDepthBuffer()
{
   auto db_depth_base = getRegister<latte::DB_DEPTH_BASE>(latte::Register::DB_DEPTH_BASE);
   auto &active = mActiveDepthBuffer;

   if (!db_depth_base.BASE_256B) {
      if (active) {
         // Unbind depth buffer
         gl::glFramebufferTexture(gl::GL_FRAMEBUFFER, gl::GL_DEPTH_ATTACHMENT, 0, 0);
         active = nullptr;
      }

      return true;
   }

   // Bind depth buffer
   auto db_depth_size = getRegister<latte::DB_DEPTH_SIZE>(latte::Register::DB_DEPTH_SIZE);
   auto db_depth_info = getRegister<latte::DB_DEPTH_INFO>(latte::Register::DB_DEPTH_INFO);
   active = getDepthBuffer(db_depth_base, db_depth_size, db_depth_info);
   gl::glFramebufferTexture(gl::GL_FRAMEBUFFER, gl::GL_DEPTH_ATTACHMENT, active->object, 0);
   return true;
}

SurfaceBuffer *
GLDriver::getDepthBuffer(latte::DB_DEPTH_BASE db_depth_base,
                         latte::DB_DEPTH_SIZE db_depth_size,
                         latte::DB_DEPTH_INFO db_depth_info)
{
   auto baseAddress = (db_depth_base.BASE_256B << 8) & 0xFFFFF800;
   auto pitch_tile_max = db_depth_size.PITCH_TILE_MAX();
   auto slice_tile_max = db_depth_size.SLICE_TILE_MAX();

   auto pitch = static_cast<uint32_t>((pitch_tile_max + 1) * latte::MicroTileWidth);
   auto height = static_cast<uint32_t>(((slice_tile_max + 1) * (latte::MicroTileWidth * latte::MicroTileHeight)) / pitch);

   latte::SQ_DATA_FORMAT format = latte::SQ_DATA_FORMAT::FMT_INVALID;
   latte::SQ_NUM_FORMAT numFormat = latte::SQ_NUM_FORMAT_NORM;
   latte::SQ_FORMAT_COMP formatComp = latte::SQ_FORMAT_COMP_UNSIGNED;
   uint32_t degamma = 0;

   auto dbFormat = static_cast<latte::DB_DEPTH_FORMAT>(db_depth_info.FORMAT());
   switch (dbFormat) {
   case latte::DB_DEPTH_FORMAT::DEPTH_16:
      format = latte::SQ_DATA_FORMAT::FMT_16;
      numFormat = latte::SQ_NUM_FORMAT_NORM;
      formatComp = latte::SQ_FORMAT_COMP_UNSIGNED;
      degamma = 0;
      break;
   case latte::DB_DEPTH_FORMAT::DEPTH_8_24:
      format = latte::SQ_DATA_FORMAT::FMT_8_24;
      numFormat = latte::SQ_NUM_FORMAT_NORM;
      formatComp = latte::SQ_FORMAT_COMP_UNSIGNED;
      degamma = 0;
      break;
   case latte::DB_DEPTH_FORMAT::DEPTH_8_24_FLOAT:
      format = latte::SQ_DATA_FORMAT::FMT_8_24_FLOAT;
      numFormat = latte::SQ_NUM_FORMAT_SCALED;
      formatComp = latte::SQ_FORMAT_COMP_UNSIGNED;
      degamma = 0;
      break;
   case latte::DB_DEPTH_FORMAT::DEPTH_32_FLOAT:
      format = latte::SQ_DATA_FORMAT::FMT_32_FLOAT;
      numFormat = latte::SQ_NUM_FORMAT_SCALED;
      formatComp = latte::SQ_FORMAT_COMP_UNSIGNED;
      degamma = 0;
      break;
   case latte::DB_DEPTH_FORMAT::DEPTH_X24_8_32_FLOAT:
      format = latte::SQ_DATA_FORMAT::FMT_X24_8_32_FLOAT;
      numFormat = latte::SQ_NUM_FORMAT_SCALED;
      formatComp = latte::SQ_FORMAT_COMP_UNSIGNED;
      degamma = 0;
      break;

   case latte::DB_DEPTH_FORMAT::DEPTH_X8_24:
   case latte::DB_DEPTH_FORMAT::DEPTH_X8_24_FLOAT:
   case latte::DB_DEPTH_FORMAT::DEPTH_INVALID:
   default:
      gLog->debug("Skipping depth buffer with unsupported format {}", dbFormat);
      return nullptr;
   }

   // Force the format for now...
   format = latte::SQ_DATA_FORMAT::FMT_32_FLOAT;
   numFormat = latte::SQ_NUM_FORMAT_SCALED;
   formatComp = latte::SQ_FORMAT_COMP_UNSIGNED;
   degamma = 0;

   auto buffer = getSurfaceBuffer(baseAddress, pitch, height, 1, latte::SQ_TEX_DIM_2D, format, numFormat, formatComp, degamma);

   gl::glTextureParameteri(buffer->object, gl::GL_TEXTURE_MAG_FILTER, static_cast<int>(gl::GL_NEAREST));
   gl::glTextureParameteri(buffer->object, gl::GL_TEXTURE_MIN_FILTER, static_cast<int>(gl::GL_NEAREST));
   gl::glTextureParameteri(buffer->object, gl::GL_TEXTURE_WRAP_S, static_cast<int>(gl::GL_CLAMP_TO_EDGE));
   gl::glTextureParameteri(buffer->object, gl::GL_TEXTURE_WRAP_T, static_cast<int>(gl::GL_CLAMP_TO_EDGE));

   buffer->dirtyAsTexture = false;
   buffer->state = SurfaceUseState::GpuWritten;
   return buffer;
}

} // namespace opengl

} // namespace gpu
