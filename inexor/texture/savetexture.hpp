/// @file savetexture.hpp
/// everything to save images of various formats.

#pragma once

#include "inexor/engine/engine.hpp"
#include "inexor/texture/texture.hpp"

enum
{
    IMG_BMP = 0,
    IMG_TGA = 1,
    IMG_PNG = 2,
    NUMIMG
};

extern void saveimage(const char *filename, int format, ImageData &image, bool flip = false);
extern int guessimageformat(const char *filename, int format = IMG_PNG);

extern void savepng(const char *filename, ImageData &image, bool flip = false);
extern void savetga(const char *filename, ImageData &image, bool flip = false);


