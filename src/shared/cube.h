/// @file cube.h
/// Pre-compiled header file for cube engine
/// 
/// 
/// 
/// 

/// include guard protects this file from being included twice
#ifndef __CUBE_H__
#define __CUBE_H__

#define _FILE_OFFSET_BITS 64

#ifdef __GNUC__
  #define gamma __gamma
#endif

#ifdef WIN32
  /// we define our own math constants (PI, ln(2)...)
  #define _USE_MATH_DEFINES
#endif
#include <math.h>

#ifdef __GNUC__
  #undef gamma
#endif

/// essentiall C standard libraries
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <stdarg.h>
#include <limits.h>
#include <assert.h>
#include <time.h>


#ifdef WIN32
  /// only include very important Win32 API core
  #define WIN32_LEAN_AND_MEAN
  #ifdef _WIN32_WINNT
    #undef _WIN32_WINNT
  #endif
  /// use Windows XP version of WinAPI
  #define _WIN32_WINNT 0x0500

  #include "windows.h"
  #ifndef _WINDOWS
    #define _WINDOWS
  #endif

  #ifndef __GNUC__
    #include <eh.h>
    #include <dbghelp.h>
  #endif

  ///#define ZLIB_DLL
#endif


/// SDL (Simple DirectMedia Layer) libraries
/// https://www.libsdl.org/
#ifndef STANDALONE
  #include <SDL.h>
  #include <SDL_opengl.h>
#endif

/// ENET: reliable UDP networking library
/// https://github.com/lsalzman/enet
/// http://enet.bespin.org/
#include <enet/enet.h>

/// ZLIB compression library (used for map compression)
/// http://www.zlib.net/
#include <zlib.h>

/// a set of containers (vector,hashset,buffer,stream) and tools for developing
/// @warning Try to avoid using these containers. The C++ standard library is much more reliable!
#include "tools.h"

/// geometric library: vectors, quaterions, matrices and more
#include "geom.h"
/// OLD entity system
#include "ents.h"
/// command line and scripting engine
#include "command.h"

/// JSON (Javascript Object Notation) parser
/// Static data storage format
#include "json.h"

/// header files for communication between the game and Cube engine
#include "iengine.h"
#include "igame.h"


#endif /// end include guard __CUBE_H__

