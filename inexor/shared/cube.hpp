/// @file main header file for legacy code.

#ifndef __CUBE_H__
#define __CUBE_H__

#define _FILE_OFFSET_BITS 64

#include <math.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <stdarg.h>
#include <limits.h>
#include <assert.h>
#include <time.h>


#ifdef WIN32
  #ifndef WIN32_LEAN_AND_MEAN // only include very important win API core, not inflicting other libs.
	#define WIN32_LEAN_AND_MEAN
  #endif

  #include "windows.h"

#endif

#ifndef STANDALONE
  #include <SDL.h>
  #include <SDL_opengl.h>
#endif

/// ENET: reliable UDP networking library
#include <enet/enet.h>

/// ZLIB compression library (used e.g. for map compression)
#include <zlib.h>

#include "inexor/shared/tools.hpp"
#include "inexor/shared/geom.hpp"
#include "inexor/shared/ents.hpp"
#include "inexor/shared/command.hpp"

#ifndef STANDALONE
#include "inexor/engine/glexts.hpp"
#include "inexor/engine/glemu.hpp"
#endif

#include "inexor/shared/iengine.hpp"
#include "inexor/shared/igame.hpp"


#endif // __CUBE_H__

