/// @file Main texture loading and organizing routines + main texture structures.

#pragma once

#include "inexor/texture/texsettings.hpp"
#include "inexor/texture/image.hpp"
#include "inexor/shared/cube_types.hpp"
#include "inexor/texture/additionaltools.hpp" //this one is only to avoid the compiler behaviour that it doesnt build cubescript only files, so we keep a dummy "extern" to it.

/// Different Texture Types.
enum
{
    TEX_DIFFUSE = 0,
    TEX_UNKNOWN,
    TEX_DECAL,
    TEX_NORMAL,
    TEX_GLOW,
    TEX_SPEC,
    TEX_DEPTH,
    TEX_ENVMAP,
    TEX_NUM
};

/// A Texture entry, holding info about a texture on the GPU.
struct Texture
{
    enum
    {
        IMAGE = 0,
        CUBEMAP = 1,
        TYPE = 0xFF,

        STUB = 1 << 8,
        TRANSIENT = 1 << 9,
        COMPRESSED = 1 << 10,
        ALPHA = 1 << 11,
        FLAGS = 0xFF00
    };

    char *name;
    int type, w, h, xs, ys, bpp, clamp;
    bool mipmap, canreduce;
    GLuint id;
    uchar *alphamask;

    Texture() : alphamask(NULL) {}
};

/// Global used to specify this texture has not be found.
extern Texture *notexture;

extern int texalign(void *data, int w, int bpp);
extern void cleanuptexture(Texture *t);
extern uchar *loadalphamask(Texture *t);
extern void setuptexparameters(int tnum, void *pixels, int clamp, int filter, GLenum format = GL_RGB, GLenum target = GL_TEXTURE_2D);
extern void createtexture(int tnum, int w, int h, void *pixels, int clamp, int filter, GLenum component = GL_RGB, GLenum target = GL_TEXTURE_2D, int pw = 0, int ph = 0, int pitch = 0, bool resize = true, GLenum format = GL_FALSE);
extern void createcompressedtexture(int tnum, int w, int h, uchar *data, int align, int blocksize, int levels, int clamp, int filter, GLenum format, GLenum subtarget);
extern bool reloadtexture(Texture &tex);
extern bool reloadtexture(const char *name);
extern void setuptexcompress();

extern Texture *textureload(const char *name, int clamp = 0, bool mipit = true, bool msg = true, bool threadsafe = false);
extern Texture *newtexture(Texture *t, const char *rname, ImageData &s, int clamp = 0, bool mipit = true, bool canreduce = false, bool transient = false, int compress = 0);

extern bool loadimage(const char *filename, ImageData &image);

// Texture Registry:
extern Texture *registertexture(const char *name);
extern Texture *gettexture(const char *name);

