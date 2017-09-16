/// @file StackWalker_windows.hpp
/// Internal(!!) Header for the windows stackwalker.
/// @warning Don't include this file directly but CrashReporter.h instead.

#pragma once
#include <vector>
#include <string>
// #include "Stackwalker++/StackWalker.h"


static inline void printStackTrace(std::vector<std::string> &output)
{
 //   StackWalker sw(StackWalker::OptionsAll);
  //  sw.ShowCallstack(&output);
}

