/// @file Internal(!!) Header for the windows stackwalker.
/// @warning Don't include this file directly but CrashReporter.h instead.

#ifndef INEXOR_STACKWALKER_WINDOWS_H
#define INEXOR_STACKWALKER_WINDOWS_H

#include "Stackwalker++/StackWalker.h"


static inline void printStackTrace(std::vector<std::string> &output)
{
    StackWalker sw(StackWalker::OptionsAll);
    sw.ShowCallstack(&output);
}

#endif // INEXOR_STACKWALKER_WINDOWS_H
