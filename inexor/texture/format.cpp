/// @file format.cpp
/// Small helper functions to organize which OpenGL formats to use.

#include <SDL_opengl.h>                    // for GL_COMPRESSED_RGBA_S3TC_DX...
#include <algorithm>                       // for max

#include "inexor/network/SharedVar.hpp"    // for SharedVar
#include "inexor/shared/tools.hpp"         // for max
#include "inexor/texture/format.hpp"
#include "inexor/texture/texsettings.hpp"  // for usetexcompress, texcompress

GLenum texformat(int bpp)
{
    switch(bpp)
    {
    case 1: return hasTRG ? GL_RED : GL_LUMINANCE;
    case 2: return hasTRG ? GL_RG : GL_LUMINANCE_ALPHA;
    case 3: return GL_RGB;
    case 4: return GL_RGBA;
    default: return 0;
    }
}

bool alphaformat(GLenum format)
{
    switch(format)
    {
    case GL_ALPHA:
    case GL_LUMINANCE_ALPHA:
    case GL_RG:
    case GL_RGBA:
        return true;
    default:
        return false;
    }
}

GLenum uncompressedformat(GLenum format)
{
    switch(format)
    {
    case GL_COMPRESSED_ALPHA:
        return GL_ALPHA;
    case GL_COMPRESSED_LUMINANCE:
    case GL_COMPRESSED_LUMINANCE_LATC1_EXT:
        return GL_LUMINANCE;
    case GL_COMPRESSED_LUMINANCE_ALPHA:
    case GL_COMPRESSED_LUMINANCE_ALPHA_LATC2_EXT:
        return GL_LUMINANCE_ALPHA;
    case GL_COMPRESSED_RED:
    case GL_COMPRESSED_RED_RGTC1:
        return GL_RED;
    case GL_COMPRESSED_RG:
    case GL_COMPRESSED_RG_RGTC2:
        return GL_RG;
    case GL_COMPRESSED_RGB:
    case GL_COMPRESSED_RGB_S3TC_DXT1_EXT:
        return GL_RGB;
    case GL_COMPRESSED_RGBA:
    case GL_COMPRESSED_RGBA_S3TC_DXT1_EXT:
    case GL_COMPRESSED_RGBA_S3TC_DXT3_EXT:
    case GL_COMPRESSED_RGBA_S3TC_DXT5_EXT:
        return GL_RGBA;
    }
    return GL_FALSE;
}

GLenum compressedformat(GLenum format, int w, int h, int force = 0)
{
    if(usetexcompress && texcompress && force >= 0 && (force || max(w, h) >= texcompress)) switch(format)
    {
    case GL_RGB5:
    case GL_RGB8:
    case GL_RGB: return usetexcompress > 1 ? GL_COMPRESSED_RGB_S3TC_DXT1_EXT : GL_COMPRESSED_RGB;
    case GL_RGB5_A1: return usetexcompress > 1 ? GL_COMPRESSED_RGBA_S3TC_DXT1_EXT : GL_COMPRESSED_RGBA;
    case GL_RGBA: return usetexcompress > 1 ? GL_COMPRESSED_RGBA_S3TC_DXT5_EXT : GL_COMPRESSED_RGBA;
    case GL_RED:
    case GL_R8: return hasRGTC ? (usetexcompress > 1 ? GL_COMPRESSED_RED_RGTC1 : GL_COMPRESSED_RED) : (usetexcompress > 1 ? GL_COMPRESSED_RGB_S3TC_DXT1_EXT : GL_COMPRESSED_RGB);
    case GL_RG:
    case GL_RG8: return hasRGTC ? (usetexcompress > 1 ? GL_COMPRESSED_RG_RGTC2 : GL_COMPRESSED_RG) : (usetexcompress > 1 ? GL_COMPRESSED_RGBA_S3TC_DXT5_EXT : GL_COMPRESSED_RGBA);
    case GL_LUMINANCE:
    case GL_LUMINANCE8: return hasLATC ? (usetexcompress > 1 ? GL_COMPRESSED_LUMINANCE_LATC1_EXT : GL_COMPRESSED_LUMINANCE) : (usetexcompress > 1 ? GL_COMPRESSED_RGB_S3TC_DXT1_EXT : GL_COMPRESSED_RGB);
    case GL_LUMINANCE_ALPHA:
    case GL_LUMINANCE8_ALPHA8: return hasLATC ? (usetexcompress > 1 ? GL_COMPRESSED_LUMINANCE_ALPHA_LATC2_EXT : GL_COMPRESSED_LUMINANCE_ALPHA) : (usetexcompress > 1 ? GL_COMPRESSED_RGBA_S3TC_DXT5_EXT : GL_COMPRESSED_RGBA);
    }
    return format;
}

const GLint *swizzlemask(GLenum format)
{
    static const GLint luminance[4] = { GL_RED, GL_RED, GL_RED, GL_ONE };
    static const GLint luminancealpha[4] = { GL_RED, GL_RED, GL_RED, GL_GREEN };
    switch(format)
    {
        case GL_RED: return luminance;
        case GL_RG: return luminancealpha;
    }
    return NULL;
}

GLenum textarget(GLenum subtarget)
{
    switch(subtarget)
    {
    case GL_TEXTURE_CUBE_MAP_POSITIVE_X:
    case GL_TEXTURE_CUBE_MAP_NEGATIVE_X:
    case GL_TEXTURE_CUBE_MAP_POSITIVE_Y:
    case GL_TEXTURE_CUBE_MAP_NEGATIVE_Y:
    case GL_TEXTURE_CUBE_MAP_POSITIVE_Z:
    case GL_TEXTURE_CUBE_MAP_NEGATIVE_Z:
        return GL_TEXTURE_CUBE_MAP;
    }
    return subtarget;
}

int formatsize(GLenum format)
{
    switch(format)
    {
    case GL_RED:
    case GL_LUMINANCE:
    case GL_ALPHA: return 1;
    case GL_RG:
    case GL_LUMINANCE_ALPHA: return 2;
    case GL_RGB: return 3;
    case GL_RGBA: return 4;
    default: return 4;
    }
}
