#include <memory>
#include <spdlog/spdlog.h>
#include "hardwaretests.h"
#include "libcpu/cpu.h"
#include "libcpu/mem.h"

std::shared_ptr<spdlog::logger>
gLog;

static int runResult;

int main(int argc, char *argv[])
{
   gLog = std::make_shared<spdlog::logger>("logger", std::make_shared<spdlog::sinks::stdout_sink_st>());
   gLog->set_level(spdlog::level::debug);

   mem::initialise();
   cpu::initialise();

   // Force diasble JIT until we fix cpu::jit::clearCache
   cpu::setJitMode(cpu::jit_mode::disabled);

   // We need to run the tests on a core.
   cpu::setCoreEntrypointHandler(
      []() {
         if (cpu::this_core::id() == 1) {
            // Run the tests on only a single core.
            runResult = hwtest::runTests("tests/cpu/wiiu") ? 0 : 1;
         }
      });

   cpu::start();
   cpu::join();

   system("PAUSE");
   return runResult;
}
