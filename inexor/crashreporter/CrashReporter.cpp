/// @file CrashReporter.cpp
/// the CrashReporter instance you want to have somewhere in your code.


#ifndef __MINGW32__ // we do not allow MinGW stackwalking atm.
#include "inexor/crashreporter/CrashReporter.hpp"
#include "inexor/util/StringFormatter.hpp"
#ifdef WIN32
#include "inexor/crashreporter/StackWalker_windows.hpp"
#else
#include "inexor/crashreporter/StackWalker_posix.hpp"
#endif

extern void fatal(std::vector<std::string> &output);

namespace inexor {
namespace crashreporter {

using namespace inexor::util;

/// This function serves as callback for the signals function.
/// It gets executed when an instance of the crashreporter class exists in your code
/// and it receives a signal by the OS to terminate the program.
void abortHandler(int signum)
{
    std::vector<std::string> output;

    // get the name of the signal:
    const char* name = "UNKNOWN_SIGNAL";
    switch(signum)
    {
        case SIGABRT: name = "SIGABRT";  break;
        case SIGSEGV: name = "SIGSEGV";  break;
        case SIGILL:  name = "SIGILL";   break;
        case SIGFPE:  name = "SIGFPE";   break;
      #ifndef WIN32
        case SIGBUS:  name = "SIGBUS";   break;
      #endif
    }
    std::string out = fmt << "Caught signal " << signum << " (" << name << ")\n\n";
    output.push_back(std::move(out));

    printStackTrace(output);

    fatal(output);
}

} // namespace crashreporter
} // namespace inexor

#endif // __MINGW32__
