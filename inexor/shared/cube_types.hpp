/// Basic type definitions.

#pragma once

#include <stddef.h>

typedef unsigned char uchar;
typedef unsigned short ushort;
typedef unsigned int uint;
typedef unsigned long ulong;
typedef signed long long int llong;
typedef unsigned long long int ullong;


/// maximal cube-string length.
#define MAXSTRLEN 260
/// cube-strings (char arrays of fixed size).
typedef char string[MAXSTRLEN];

/// Path divide character, \ on win, otherwise /.
#ifdef WIN32
#define PATHDIV '\\'
#else
#define PATHDIV '/'
#endif

// some important mathematical constants:
#define PI  (3.1415927f)
#define PI2 (2*PI)
#define SQRT2 (1.4142136f)
#define SQRT3 (1.7320508f)
#define RAD (PI / 180.0f)

#ifndef NULL
#define NULL 0
#endif
