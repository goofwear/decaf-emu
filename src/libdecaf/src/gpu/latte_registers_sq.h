#pragma once
#include "common/types.h"
#include "common/bitfield.h"
#include "latte_enum_sq.h"

namespace latte
{

// ALU Constant store data for use in DX9 mode (DX10 mode uses the constant-cache
// instead and this constant-file is not available).
// Constants 0-225 are reserved for pixel shader
// Constants 256-511 are reserved for vertex shader
struct SQ_ALU_CONSTANT0_0
{
   uint32_t value;
   float X;
};

struct SQ_ALU_CONSTANT1_0
{
   uint32_t value;
   float Y;
};

struct SQ_ALU_CONSTANT2_0
{
   uint32_t value;
   float Z;
};

struct SQ_ALU_CONSTANT3_0
{
   uint32_t value;
   float W;
};

struct SQ_CONFIG : Bitfield<SQ_CONFIG, uint32_t>
{
   BITFIELD_ENTRY(0, 1, bool, VC_ENABLE);
   BITFIELD_ENTRY(1, 1, bool, EXPORT_SRC_C);
   BITFIELD_ENTRY(2, 1, bool, DX9_CONSTS);
   BITFIELD_ENTRY(3, 1, bool, ALU_INST_PREFER_VECTOR);
   BITFIELD_ENTRY(4, 1, bool, DX10_CLAMP);
   BITFIELD_ENTRY(5, 1, bool, ALU_PREFER_ONE_WATERFALL);
   BITFIELD_ENTRY(6, 1, bool, ALU_MAX_ONE_WATERFALL);
   BITFIELD_ENTRY(8, 2, uint32_t, CLAUSE_SEQ_PRIO);
   BITFIELD_ENTRY(10, 1, bool, NO_GPR_CLAMP);
   BITFIELD_ENTRY(11, 1, bool, EN_TEX_SKEW);
   BITFIELD_ENTRY(24, 2, uint32_t, PS_PRIO);
   BITFIELD_ENTRY(26, 2, uint32_t, VS_PRIO);
   BITFIELD_ENTRY(28, 2, uint32_t, GS_PRIO);
   BITFIELD_ENTRY(30, 2, uint32_t, ES_PRIO);
};

// Space allocated to a single GS output vertex in GS Temp Buffer. This defines the
// size of a single vertex output by the GS.Multiple vertices can be output so long
// as the total output size does not exceed SQ_GSVS_RING_ITEMSIZE.
struct SQ_GS_VERT_ITEMSIZE : Bitfield<SQ_GS_VERT_ITEMSIZE, uint32_t>
{
   BITFIELD_ENTRY(0, 15, uint32_t, ITEMSIZE);
};

// Defines how GPR space is divided among the 4 thread types.
struct SQ_GPR_RESOURCE_MGMT_1 : Bitfield<SQ_GPR_RESOURCE_MGMT_1, uint32_t>
{
   BITFIELD_ENTRY(0, 8, uint32_t, NUM_PS_GPRS);
   BITFIELD_ENTRY(16, 8, uint32_t, NUM_VS_GPRS);
   BITFIELD_ENTRY(27, 1, bool, DYN_GPR_ENABLE);
   BITFIELD_ENTRY(28, 4, uint32_t, NUM_CLAUSE_TEMP_GPRS);
};

// Defines how GPR space is divided among the 4 thread types.
struct SQ_GPR_RESOURCE_MGMT_2 : Bitfield<SQ_GPR_RESOURCE_MGMT_2, uint32_t>
{
   BITFIELD_ENTRY(0, 8, uint32_t, NUM_GS_GPRS);
   BITFIELD_ENTRY(16, 8, uint32_t, NUM_ES_GPRS);
};

// Used for SQ_CF_INST_LOOP and SQ_CF_INST_LOOP_NO_AL
struct SQ_LOOP_CONST_DX9_0 : Bitfield<SQ_LOOP_CONST_DX9_0, uint32_t>
{
   BITFIELD_ENTRY(0, 12, uint32_t, COUNT);
   BITFIELD_ENTRY(12, 12, uint32_t, INIT);
   BITFIELD_ENTRY(24, 8, uint32_t, INC);
};

// Used for SQ_CF_INST_LOOP_DX10
union SQ_LOOP_CONST_DX10_0
{
   uint32_t value;
   uint32_t COUNT;
};

// Defines how thread stack space is divided among the thread types
struct SQ_STACK_RESOURCE_MGMT_1 : Bitfield<SQ_STACK_RESOURCE_MGMT_1, uint32_t>
{
   BITFIELD_ENTRY(0, 12, uint32_t, NUM_PS_STACK_ENTRIES);
   BITFIELD_ENTRY(16, 12, uint32_t, NUM_VS_STACK_ENTRIES);
};

// Defines how thread stack space is divided among the thread types
struct SQ_STACK_RESOURCE_MGMT_2 : Bitfield<SQ_STACK_RESOURCE_MGMT_2, uint32_t>
{
   BITFIELD_ENTRY(0, 12, uint32_t, NUM_GS_STACK_ENTRIES);
   BITFIELD_ENTRY(16, 12, uint32_t, NUM_ES_STACK_ENTRIES);
};

// Defines how thread space is divided among the thread types
struct SQ_THREAD_RESOURCE_MGMT : Bitfield<SQ_THREAD_RESOURCE_MGMT, uint32_t>
{
   BITFIELD_ENTRY(0, 8, uint32_t, NUM_PS_THREADS);
   BITFIELD_ENTRY(8, 8, uint32_t, NUM_VS_THREADS);
   BITFIELD_ENTRY(16, 8, uint32_t, NUM_GS_THREADS);
   BITFIELD_ENTRY(24, 8, uint32_t, NUM_ES_THREADS);
};

union SQ_VTX_CONSTANT_WORD0_N
{
   uint32_t value;
   uint32_t BASE_ADDRESS;
};

union SQ_VTX_CONSTANT_WORD1_N
{
   uint32_t value;
   uint32_t SIZE;
};

struct SQ_VTX_CONSTANT_WORD2_N : Bitfield<SQ_VTX_CONSTANT_WORD2_N, uint32_t>
{
   BITFIELD_ENTRY(0, 8, uint32_t, BASE_ADDRESS_HI);
   BITFIELD_ENTRY(8, 11, uint32_t, STRIDE);
   BITFIELD_ENTRY(19, 1, SQ_VTX_CLAMP, CLAMP_X);
   BITFIELD_ENTRY(20, 6, SQ_DATA_FORMAT, DATA_FORMAT);
   BITFIELD_ENTRY(26, 2, SQ_NUM_FORMAT, NUM_FORMAT_ALL);
   BITFIELD_ENTRY(28, 1, SQ_FORMAT_COMP, FORMAT_COMP_ALL);
   BITFIELD_ENTRY(29, 1, SQ_SRF_MODE, SRF_MODE_ALL);
   BITFIELD_ENTRY(30, 2, SQ_ENDIAN, ENDIAN_SWAP);
};

struct SQ_VTX_CONSTANT_WORD3_N : Bitfield<SQ_VTX_CONSTANT_WORD3_N, uint32_t>
{
   BITFIELD_ENTRY(0, 2, uint32_t, MEM_REQUEST_SIZE);
   BITFIELD_ENTRY(2, 1, bool, UNCACHED);
};

struct SQ_VTX_CONSTANT_WORD6_N : Bitfield<SQ_VTX_CONSTANT_WORD6_N, uint32_t>
{
   BITFIELD_ENTRY(30, 2, SQ_TEX_VTX_TYPE, TYPE);
};

// Vertex fetch base location
union SQ_VTX_BASE_VTX_LOC
{
   uint32_t value;
   uint32_t OFFSET;
};

// Resource requirements to run the GS program
struct SQ_PGM_RESOURCES_GS : Bitfield<SQ_PGM_RESOURCES_GS, uint32_t>
{
   BITFIELD_ENTRY(0, 8, uint32_t, NUM_GPRS);
   BITFIELD_ENTRY(8, 8, uint32_t, STACK_SIZE);
   BITFIELD_ENTRY(21, 1, bool, DX10_CLAMP);
   BITFIELD_ENTRY(22, 1, bool, PRIME_CACHE_PGM_EN);
   BITFIELD_ENTRY(23, 1, bool, PRIME_CACHE_ON_DRAW);
   BITFIELD_ENTRY(24, 3, uint32_t, FETCH_CACHE_LINES);
   BITFIELD_ENTRY(28, 1, bool, UNCACHED_FIRST_INST);
   BITFIELD_ENTRY(29, 1, bool, PRIME_CACHE_ENABLE);
   BITFIELD_ENTRY(30, 1, bool, PRIME_CACHE_ON_CONST);
};

// Resource requirements to run the Vertex Shader program
struct SQ_PGM_RESOURCES_VS : Bitfield<SQ_PGM_RESOURCES_VS, uint32_t>
{
   BITFIELD_ENTRY(0, 8, uint32_t, NUM_GPRS);
   BITFIELD_ENTRY(8, 8, uint32_t, STACK_SIZE);
   BITFIELD_ENTRY(21, 1, bool, DX10_CLAMP);
   BITFIELD_ENTRY(22, 1, bool, PRIME_CACHE_PGM_EN);
   BITFIELD_ENTRY(23, 1, bool, PRIME_CACHE_ON_DRAW);
   BITFIELD_ENTRY(24, 3, uint32_t, FETCH_CACHE_LINES);
   BITFIELD_ENTRY(28, 1, bool, UNCACHED_FIRST_INST);
   BITFIELD_ENTRY(29, 1, bool, PRIME_CACHE_ENABLE);
   BITFIELD_ENTRY(30, 1, bool, PRIME_CACHE_ON_CONST);
};

// Resource requirements to run the Pixel Shader program
struct SQ_PGM_RESOURCES_PS : Bitfield<SQ_PGM_RESOURCES_PS, uint32_t>
{
   BITFIELD_ENTRY(0, 8, uint32_t, NUM_GPRS);
   BITFIELD_ENTRY(8, 8, uint32_t, STACK_SIZE);
   BITFIELD_ENTRY(21, 1, bool, DX10_CLAMP);
   BITFIELD_ENTRY(22, 1, bool, PRIME_CACHE_PGM_EN);
   BITFIELD_ENTRY(23, 1, bool, PRIME_CACHE_ON_DRAW);
   BITFIELD_ENTRY(24, 3, uint32_t, FETCH_CACHE_LINES);
   BITFIELD_ENTRY(28, 1, bool, UNCACHED_FIRST_INST);
   BITFIELD_ENTRY(29, 1, bool, PRIME_CACHE_ENABLE);
   BITFIELD_ENTRY(30, 1, bool, PRIME_CACHE_ON_CONST);
   BITFIELD_ENTRY(31, 1, bool, CLAMP_CONSTS);
};

// Resource requirements to run the Fetch Shader program
struct SQ_PGM_RESOURCES_FS : Bitfield<SQ_PGM_RESOURCES_FS, uint32_t>
{
   BITFIELD_ENTRY(0, 8, uint32_t, NUM_GPRS);
   BITFIELD_ENTRY(8, 8, uint32_t, STACK_SIZE);
   BITFIELD_ENTRY(21, 1, bool, DX10_CLAMP);
};

// Memory address of the (256-byte aligned) first CF instruction of the shader code for the fetch shader(FS)
union SQ_PGM_START_FS
{
   uint32_t value;
   uint32_t PGM_START;
};

// Size >> 3
union SQ_PGM_SIZE_FS
{
   uint32_t value;
   uint32_t PGM_SIZE;
};

// Memory address of the (256-byte aligned) first CF instruction of the shader code for the fetch shader(VS)
union SQ_PGM_START_VS
{
   uint32_t value;
   uint32_t PGM_START;
};

// Size >> 3
union SQ_PGM_SIZE_VS
{
   uint32_t value;
   uint32_t PGM_SIZE;
};

// Memory address of the (256-byte aligned) first CF instruction of the shader code for the fetch shader(PS)
union SQ_PGM_START_PS
{
   uint32_t value;
   uint32_t PGM_START;
};

// Size >> 3
union SQ_PGM_SIZE_PS
{
   uint32_t value;
   uint32_t PGM_SIZE;
};

// Defines the exports from the Pixel Shader Program.
struct SQ_PGM_EXPORTS_PS : Bitfield<SQ_PGM_EXPORTS_PS, uint32_t>
{
   BITFIELD_ENTRY(0, 5, uint32_t, EXPORT_MODE);
};

// This register is used to clear the contents of the vertex semantic table.
// Entries can be cleared independently -- each has one bit in this register to clear or leave alone.
union SQ_VTX_SEMANTIC_CLEAR
{
   uint32_t value;
   uint32_t CLEAR;
};

struct SQ_VTX_SEMANTIC_N : Bitfield<SQ_VTX_SEMANTIC_N, uint32_t>
{
   BITFIELD_ENTRY(0, 8, uint32_t, SEMANTIC_ID);
};

using SQ_VTX_SEMANTIC_0 = SQ_VTX_SEMANTIC_N;
using SQ_VTX_SEMANTIC_1 = SQ_VTX_SEMANTIC_N;
using SQ_VTX_SEMANTIC_2 = SQ_VTX_SEMANTIC_N;
using SQ_VTX_SEMANTIC_3 = SQ_VTX_SEMANTIC_N;
using SQ_VTX_SEMANTIC_4 = SQ_VTX_SEMANTIC_N;
using SQ_VTX_SEMANTIC_5 = SQ_VTX_SEMANTIC_N;
using SQ_VTX_SEMANTIC_6 = SQ_VTX_SEMANTIC_N;
using SQ_VTX_SEMANTIC_7 = SQ_VTX_SEMANTIC_N;
using SQ_VTX_SEMANTIC_8 = SQ_VTX_SEMANTIC_N;
using SQ_VTX_SEMANTIC_9 = SQ_VTX_SEMANTIC_N;
using SQ_VTX_SEMANTIC_10 = SQ_VTX_SEMANTIC_N;
using SQ_VTX_SEMANTIC_11 = SQ_VTX_SEMANTIC_N;
using SQ_VTX_SEMANTIC_12 = SQ_VTX_SEMANTIC_N;
using SQ_VTX_SEMANTIC_13 = SQ_VTX_SEMANTIC_N;
using SQ_VTX_SEMANTIC_14 = SQ_VTX_SEMANTIC_N;
using SQ_VTX_SEMANTIC_15 = SQ_VTX_SEMANTIC_N;
using SQ_VTX_SEMANTIC_16 = SQ_VTX_SEMANTIC_N;
using SQ_VTX_SEMANTIC_17 = SQ_VTX_SEMANTIC_N;
using SQ_VTX_SEMANTIC_18 = SQ_VTX_SEMANTIC_N;
using SQ_VTX_SEMANTIC_19 = SQ_VTX_SEMANTIC_N;
using SQ_VTX_SEMANTIC_20 = SQ_VTX_SEMANTIC_N;
using SQ_VTX_SEMANTIC_21 = SQ_VTX_SEMANTIC_N;
using SQ_VTX_SEMANTIC_22 = SQ_VTX_SEMANTIC_N;
using SQ_VTX_SEMANTIC_23 = SQ_VTX_SEMANTIC_N;
using SQ_VTX_SEMANTIC_24 = SQ_VTX_SEMANTIC_N;
using SQ_VTX_SEMANTIC_25 = SQ_VTX_SEMANTIC_N;
using SQ_VTX_SEMANTIC_26 = SQ_VTX_SEMANTIC_N;
using SQ_VTX_SEMANTIC_27 = SQ_VTX_SEMANTIC_N;
using SQ_VTX_SEMANTIC_28 = SQ_VTX_SEMANTIC_N;
using SQ_VTX_SEMANTIC_29 = SQ_VTX_SEMANTIC_N;
using SQ_VTX_SEMANTIC_30 = SQ_VTX_SEMANTIC_N;
using SQ_VTX_SEMANTIC_31 = SQ_VTX_SEMANTIC_N;

struct SQ_TEX_RESOURCE_WORD0_N : Bitfield<SQ_TEX_RESOURCE_WORD0_N, uint32_t>
{
   BITFIELD_ENTRY(0, 3, SQ_TEX_DIM, DIM);
   BITFIELD_ENTRY(3, 4, SQ_TILE_MODE, TILE_MODE);
   BITFIELD_ENTRY(7, 1, uint32_t, TILE_TYPE);
   BITFIELD_ENTRY(8, 11, uint32_t, PITCH);
   BITFIELD_ENTRY(19, 13, uint32_t, TEX_WIDTH);
};

struct SQ_TEX_RESOURCE_WORD1_N : Bitfield<SQ_TEX_RESOURCE_WORD1_N, uint32_t>
{
   BITFIELD_ENTRY(0, 13, uint32_t, TEX_HEIGHT);
   BITFIELD_ENTRY(13, 13, uint32_t, TEX_DEPTH);
   BITFIELD_ENTRY(26, 6, SQ_DATA_FORMAT, DATA_FORMAT);
};

struct SQ_TEX_RESOURCE_WORD2_N : Bitfield<SQ_TEX_RESOURCE_WORD2_N, uint32_t>
{
   BITFIELD_ENTRY(0, 3, uint32_t, SWIZZLE);
   BITFIELD_ENTRY(0, 32, uint32_t, BASE_ADDRESS);
};

struct SQ_TEX_RESOURCE_WORD3_N : Bitfield<SQ_TEX_RESOURCE_WORD3_N, uint32_t>
{
   BITFIELD_ENTRY(0, 32, uint32_t, MIP_ADDRESS);
};

struct SQ_TEX_RESOURCE_WORD4_N : Bitfield<SQ_TEX_RESOURCE_WORD4_N, uint32_t>
{
   BITFIELD_ENTRY(0, 2, SQ_FORMAT_COMP, FORMAT_COMP_X);
   BITFIELD_ENTRY(2, 2, SQ_FORMAT_COMP, FORMAT_COMP_Y);
   BITFIELD_ENTRY(4, 2, SQ_FORMAT_COMP, FORMAT_COMP_Z);
   BITFIELD_ENTRY(6, 2, SQ_FORMAT_COMP, FORMAT_COMP_W);
   BITFIELD_ENTRY(8, 2, SQ_NUM_FORMAT, NUM_FORMAT_ALL);
   BITFIELD_ENTRY(10, 1, SQ_SRF_MODE, SRF_MODE_ALL);
   BITFIELD_ENTRY(11, 1, bool, FORCE_DEGAMMA);
   BITFIELD_ENTRY(12, 2, SQ_ENDIAN, ENDIAN_SWAP);
   BITFIELD_ENTRY(14, 2, uint32_t, REQUEST_SIZE);
   BITFIELD_ENTRY(16, 3, SQ_SEL, DST_SEL_X);
   BITFIELD_ENTRY(19, 3, SQ_SEL, DST_SEL_Y);
   BITFIELD_ENTRY(22, 3, SQ_SEL, DST_SEL_Z);
   BITFIELD_ENTRY(25, 3, SQ_SEL, DST_SEL_W);
   BITFIELD_ENTRY(28, 3, uint32_t, BASE_LEVEL);
};

struct SQ_TEX_RESOURCE_WORD5_N : Bitfield<SQ_TEX_RESOURCE_WORD5_N, uint32_t>
{
   BITFIELD_ENTRY(0, 4, uint32_t, LAST_LEVEL);
   BITFIELD_ENTRY(4, 13, uint32_t, BASE_ARRAY);
   BITFIELD_ENTRY(17, 13, uint32_t, LAST_ARRAY);
   BITFIELD_ENTRY(30, 2, uint32_t, YUV_CONV);
};

struct SQ_TEX_RESOURCE_WORD6_N : Bitfield<SQ_TEX_RESOURCE_WORD6_N, uint32_t>
{
   BITFIELD_ENTRY(0, 2, SQ_TEX_MPEG_CLAMP, MPEG_CLAMP);
   BITFIELD_ENTRY(2, 3, uint32_t, MAX_ANISO_RATIO);
   BITFIELD_ENTRY(5, 3, uint32_t, PERF_MODULATION);
   BITFIELD_ENTRY(8, 1, bool, INTERLACED);
   BITFIELD_ENTRY(9, 4, uint32_t, ADVIS_FAULT_LOD);
   BITFIELD_ENTRY(13, 6, uint32_t, ADVIS_CLAMP_LOD);
   BITFIELD_ENTRY(30, 2, SQ_TEX_VTX_TYPE, TYPE);
};

struct SQ_TEX_SAMPLER_WORD0_N : Bitfield<SQ_TEX_SAMPLER_WORD0_N, uint32_t>
{
   BITFIELD_ENTRY(0, 3, SQ_TEX_CLAMP, CLAMP_X);
   BITFIELD_ENTRY(3, 3, SQ_TEX_CLAMP, CLAMP_Y);
   BITFIELD_ENTRY(6, 3, SQ_TEX_CLAMP, CLAMP_Z);
   BITFIELD_ENTRY(9, 3, SQ_TEX_XY_FILTER, XY_MAG_FILTER);
   BITFIELD_ENTRY(12, 3, SQ_TEX_XY_FILTER, XY_MIN_FILTER);
   BITFIELD_ENTRY(15, 2, SQ_TEX_Z_FILTER, Z_FILTER);
   BITFIELD_ENTRY(17, 2, SQ_TEX_Z_FILTER, MIP_FILTER);
   BITFIELD_ENTRY(19, 3, SQ_TEX_ANISO, MAX_ANISO_RATIO);
   BITFIELD_ENTRY(22, 2, SQ_TEX_BORDER_COLOR, BORDER_COLOR_TYPE);
   BITFIELD_ENTRY(24, 1, bool, POINT_SAMPLING_CLAMP);
   BITFIELD_ENTRY(25, 1, bool, TEX_ARRAY_OVERRIDE);
   BITFIELD_ENTRY(26, 3, SQ_TEX_DEPTH_COMPARE, DEPTH_COMPARE_FUNCTION);
   BITFIELD_ENTRY(29, 2, SQ_TEX_CHROMA_KEY, CHROMA_KEY);
   BITFIELD_ENTRY(31, 1, bool, LOD_USES_MINOR_AXIS);
};

struct SQ_TEX_SAMPLER_WORD1_N : Bitfield<SQ_TEX_SAMPLER_WORD1_N, uint32_t>
{
   BITFIELD_ENTRY(0, 10, uint32_t, MIN_LOD);
   BITFIELD_ENTRY(10, 10, uint32_t, MAX_LOD);
   BITFIELD_ENTRY(20, 12, uint32_t, LOD_BIAS);
};

struct SQ_TEX_SAMPLER_WORD2_N : Bitfield<SQ_TEX_SAMPLER_WORD2_N, uint32_t>
{
   BITFIELD_ENTRY(0, 12, uint32_t, LOD_BIAS_SEC);
   BITFIELD_ENTRY(12, 1, bool, MC_COORD_TRUNCATE);
   BITFIELD_ENTRY(13, 1, bool, FORCE_DEGAMMA);
   BITFIELD_ENTRY(14, 1, bool, HIGH_PRECISION_FILTER);
   BITFIELD_ENTRY(15, 3, uint32_t, PERF_MIP);
   BITFIELD_ENTRY(18, 2, uint32_t, PERF_Z);
   BITFIELD_ENTRY(20, 6, uint32_t, ANISO_BIAS);
   BITFIELD_ENTRY(26, 1, bool, FETCH_4);
   BITFIELD_ENTRY(27, 1, bool, SAMPLE_IS_PCF);
   BITFIELD_ENTRY(28, 1, SQ_TEX_ROUNDING_MODE, TRUNCATE_COORD);
   BITFIELD_ENTRY(29, 1, bool, DISABLE_CUBE_WRAP);
   BITFIELD_ENTRY(31, 1, bool, TYPE);
};

} // namespace latte
