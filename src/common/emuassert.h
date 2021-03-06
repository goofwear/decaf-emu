#pragma once
#include <stdexcept>
#include <string>

#define EMULATOR_ASSERTIONS

// In the future, we should probably support a version that has a message

#ifdef EMULATOR_ASSERTIONS

static void
_emuassert(bool x, const char *stmt)
{
   if (!x) {
      throw std::logic_error(stmt);
   }
}

#define emuassert(x) _emuassert(!!(x), #x)

#else // ifdef EMULATOR_ASSERTIONS

#define emuassert(x) ((void)0)

#endif // EMULATOR_ASSERTIONS
