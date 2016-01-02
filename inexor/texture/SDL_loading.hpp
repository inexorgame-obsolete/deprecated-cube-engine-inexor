/// @file Wrapper for the SDL API calls used to load textures.

#ifndef INEXOR_TEX_SDL_LOADING_H
#define INEXOR_TEX_SDL_LOADING_H

#include "SDL_image.h"

extern SDL_Surface *wrapsurface(void *data, int width, int height, int bpp);

extern bool canloadsurface(const char *name);
extern SDL_Surface *loadsurface(const char *name);

#endif //INEXOR_TEX_SDL_LOADING_H
