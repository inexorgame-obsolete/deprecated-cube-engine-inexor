/// @file Texture modifiers mainly applied on load.

#pragma once

#include "inexor/shared/geom.hpp"
#include "inexor/shared/cube_loops.hpp"
#include "inexor/shared/cube_types.hpp"

#include <SDL.h>
#include <SDL_opengl.h>

#include <algorithm>

/// Structure holding the Raw Pixel Data and minimum image info.
/// Used when loading/modifying a texture.
struct ImageData
{
    int w, h, bpp, levels, align, pitch;
    GLenum compressed;
    uchar *data;
    void *owner;
    void(*freefunc)(void *);

    ImageData()
        : data(NULL), owner(NULL), freefunc(NULL)
    {
    }


    ImageData(int nw, int nh, int nbpp, int nlevels = 1, int nalign = 0, GLenum ncompressed = GL_FALSE)
    {
        setdata(NULL, nw, nh, nbpp, nlevels, nalign, ncompressed);
    }

    ImageData(int nw, int nh, int nbpp, uchar *data)
        : owner(NULL), freefunc(NULL)
    {
        setdata(data, nw, nh, nbpp);
    }

    ImageData(SDL_Surface *s) { wrap(s); }
    ~ImageData() { cleanup(); }

    void setdata(uchar *ndata, int nw, int nh, int nbpp, int nlevels = 1, int nalign = 0, GLenum ncompressed = GL_FALSE)
    {
        w = nw;
        h = nh;
        bpp = nbpp;
        levels = nlevels;
        align = nalign;
        pitch = align ? 0 : w*bpp;
        compressed = ncompressed;
        data = ndata ? ndata : new uchar[calcsize()];
        if (!ndata) { owner = this; freefunc = NULL; }
    }

    int calclevelsize(int level) const
    {
        return ((std::max(w >> level, 1) + align - 1) / align)*((std::max(h >> level, 1) + align - 1) / align)*bpp;
    }

    int calcsize() const
    {
        if (!align) return w*h*bpp;
        int lw = w, lh = h,
            size = 0;
        loopi(levels)
        {
            if (lw <= 0) lw = 1;
            if (lh <= 0) lh = 1;
            size += ((lw + align - 1) / align)*((lh + align - 1) / align)*bpp;
            if (lw*lh == 1) break;
            lw >>= 1;
            lh >>= 1;
        }
        return size;
    }

    void disown()
    {
        data = NULL;
        owner = NULL;
        freefunc = NULL;
    }

    void cleanup()
    {
        if (owner == this) delete[] data;
        else if (freefunc) (*freefunc)(owner);
        disown();
    }

    void replace(ImageData &d)
    {
        cleanup();
        *this = d;
        if (owner == &d) owner = this;
        d.disown();
    }

    void wrap(SDL_Surface *s)
    {
        setdata((uchar *)s->pixels, s->w, s->h, s->format->BytesPerPixel);
        pitch = s->pitch;
        owner = s;
        freefunc = (void(*)(void *))SDL_FreeSurface;
    }
};

extern void scaletexture(uchar *src, uint sw, uint sh, uint bpp, uint pitch, uchar *dst, uint dw, uint dh);
extern void resizetexture(int w, int h, bool mipmap, bool canreduce, GLenum target, int compress, int &tw, int &th);
extern void scaleimage(ImageData &s, int w, int h);

extern void texoffset(ImageData &s, int xoffset, int yoffset);
extern void texrotate(ImageData &s, int numrots, bool isnormalmap = false);
extern void texreorient(ImageData &s, bool flipx, bool flipy, bool swapxy, bool isnormalmap = false);
extern void texflip(ImageData &s);

extern void texmad(ImageData &s, const vec &mul, const vec &add);
extern void texcolorify(ImageData &s, const vec &color, vec weights);
extern void texcolormask(ImageData &s, const vec &color1, const vec &color2);
extern void texdup(ImageData &s, int srcchan, int dstchan);
extern void texmix(ImageData &s, int c1, int c2, int c3, int c4);
extern void texgrey(ImageData &s);
extern void texpremul(ImageData &s);
extern void texagrad(ImageData &s, float x2, float y2, float x1, float y1);
extern void texnormal(ImageData &s, int emphasis);
extern void texblur(ImageData &s, int n, int r);

extern void forcergbimage(ImageData &s);

extern void blurtexture(int n, int bpp, int w, int h, uchar *dst, const uchar *src, int margin = 0);
extern void blurnormals(int n, int w, int h, bvec *dst, const bvec *src, int margin = 0);


