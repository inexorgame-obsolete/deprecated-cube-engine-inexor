/// @file cube.hpp
/// main header file for legacy code.

#pragma once

// essentiall C standard libraries
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
  #include "windows.h"
#endif

#include "inexor/shared/tools.hpp"
#include "inexor/shared/geom.hpp"
#include "inexor/shared/ents.hpp"
#include "inexor/shared/command.hpp"

// header files for communication between the game and Cube engine
#include "inexor/shared/iengine.hpp"
#include "inexor/shared/igame.hpp"

