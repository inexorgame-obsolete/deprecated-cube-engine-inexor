# crash reporter

This module provides a stackwalker on crash.

The stackwalker appears as soon as an signal from the OS arrives to terminate the program (e.g. a segfault, division by zero..).

It should work on Windows, Linux and OS/X with the exception of MINGW (since our debug information are not compatible there
and we do not actually need a stackwalker on mingw currently since we use visual studio for our deployed packages).

To use this module, just include the CrashReporter.hpp somewhere in your code, make sure you got a ´fatal(std::string &output)´ function declared,
and then initialise this crashreporter-class somewhere (e.g. in your main). It does not need to be called just needs to be there.

The other files are just there to implement printstacktrace() on the different platforms.

This document served as a base for this module:
http://oroboro.com/stack-trace-on-crash/

We use http://www.codeproject.com/Articles/11132/Walking-the-callstack as library for windows (but in a shrinked form).

**The stackwalker is currently not available for MinGW builds**
If you want to change that behaviour, i'd be happy about a rewrite of this module using e.g. this lib:
* https://bitbucket.org/edd/dbg/wiki/Home
* or this one https://bitbucket.org/edd/stack_trace/wiki/Home
* or any better one
