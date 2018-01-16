#pragma once
#include "inexor/shared/cube_formatting.hpp"
#include <vector>
#include <string>

// This header exposes the fatal() functions.
// Note: You must provide the function void cleanup_application();
//       Since we want to call it before printing the error.
// TODO: investigate whether we can do this with atexit(cleanup_application). Is fatal() blocking too long?

extern void cleanup_application();
extern void fatal(const char *s, ...) PRINTFARGS(1, 2);
extern void fatal(std::vector<std::string> &output);
