/// @file Small helper functions to organize which OpenGL formats to use.

#ifndef INEXOR_TEX_FORMAT_H
#define INEXOR_TEX_FORMAT_H

#include "inexor/engine/engine.hpp" //bc hasTC

extern GLenum texformat(int bpp);
extern bool alphaformat(GLenum format);
extern GLenum uncompressedformat(GLenum format);
extern GLenum compressedformat(GLenum format, int w, int h, int force = 0);
extern GLenum textarget(GLenum subtarget);
extern int formatsize(GLenum format);

#endif //INEXOR_TEX_FORMAT_H
