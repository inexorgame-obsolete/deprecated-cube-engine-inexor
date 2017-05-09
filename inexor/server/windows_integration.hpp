#pragma once

/// @warning dangerous to include, see main trick below!

#ifdef WIN32
#ifdef STANDALONE

// We have a seperate WinMain function on windows, but want to call the usual main() afterwards: so rename it.
#undef main
#define main standalonemain

#endif
#endif
