/// @file CrashReporter.hpp
/// we catch the signals send to us by the OS on crash and display a stackwalker afterwards.
/// This works on unix as well as on windows, in release mode as well as in debug mode.
/// (Just make sure you got debuginfo on windows and initiate this class somewhere in your code,
/// as singleton or as instance in your main functin, either works)

#pragma once

#include <signal.h>

namespace inexor {
namespace crashreporter {
#ifndef __MINGW32__
    extern void abortHandler(int signum);
#endif

    class CrashReporter
    {
      public:
        CrashReporter()
        {
#ifndef __MINGW32__
            signal(SIGABRT, abortHandler);
            signal(SIGSEGV, abortHandler);
            signal(SIGILL, abortHandler);
            signal(SIGFPE, abortHandler);
#endif
        }
    };

} // namespace crashreporter
} // namespace inexor
