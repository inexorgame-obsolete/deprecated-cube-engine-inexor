/// @file Texture modifiers mainly applied on load.


#include "inexor/texture/image.hpp"
#include "inexor/texture/texsettings.hpp"
#include "inexor/texture/macros.hpp"
#include "inexor/shared/cube_endian.hpp"
#include "inexor/shared/geom.hpp"

#include <boost/algorithm/clamp.hpp> // TODO replace with std::clamp as soon as C++17 is our target.

#include <algorithm>

using boost::algorithm::clamp;
using std::min;
using std::max;
using std::swap;


#define FUNCNAME(name) name##1
#define DEFPIXEL uint OP(r, 0);
#define PIXELOP OP(r, 0);
#define BPP 1
#include "inexor/texture/scale.hpp"

#define FUNCNAME(name) name##2
#define DEFPIXEL uint OP(r, 0), OP(g, 1);
#define PIXELOP OP(r, 0); OP(g, 1);
#define BPP 2
#include "inexor/texture/scale.hpp"

#define FUNCNAME(name) name##3
#define DEFPIXEL uint OP(r, 0), OP(g, 1), OP(b, 2);
#define PIXELOP OP(r, 0); OP(g, 1); OP(b, 2);
#define BPP 3
#include "inexor/texture/scale.hpp"

#define FUNCNAME(name) name##4
#define DEFPIXEL uint OP(r, 0), OP(g, 1), OP(b, 2), OP(a, 3);
#define PIXELOP OP(r, 0); OP(g, 1); OP(b, 2); OP(a, 3);
#define BPP 4
#include "inexor/texture/scale.hpp"

void scaletexture(uchar *src, uint sw, uint sh, uint bpp, uint pitch, uchar *dst, uint dw, uint dh)
{
    if(sw == dw * 2 && sh == dh * 2)
    {
        switch(bpp)
        {
        case 1: return halvetexture1(src, sw, sh, pitch, dst);
        case 2: return halvetexture2(src, sw, sh, pitch, dst);
        case 3: return halvetexture3(src, sw, sh, pitch, dst);
        case 4: return halvetexture4(src, sw, sh, pitch, dst);
        }
    }
    else if(sw < dw || sh < dh || sw&(sw - 1) || sh&(sh - 1) || dw&(dw - 1) || dh&(dh - 1))
    {
        switch(bpp)
        {
        case 1: return scaletexture1(src, sw, sh, pitch, dst, dw, dh);
        case 2: return scaletexture2(src, sw, sh, pitch, dst, dw, dh);
        case 3: return scaletexture3(src, sw, sh, pitch, dst, dw, dh);
        case 4: return scaletexture4(src, sw, sh, pitch, dst, dw, dh);
        }
    }
    else
    {
        switch(bpp)
        {
        case 1: return shifttexture1(src, sw, sh, pitch, dst, dw, dh);
        case 2: return shifttexture2(src, sw, sh, pitch, dst, dw, dh);
        case 3: return shifttexture3(src, sw, sh, pitch, dst, dw, dh);
        case 4: return shifttexture4(src, sw, sh, pitch, dst, dw, dh);
        }
    }
}

void resizetexture(int w, int h, bool mipmap, bool canreduce, GLenum target, int compress, int &tw, int &th)
{
    int hwlimit = target == GL_TEXTURE_CUBE_MAP ? hwcubetexsize : hwtexsize,
        sizelimit = mipmap && maxtexsize ? min(maxtexsize, hwlimit) : hwlimit;
    if(compress > 0 && !usetexcompress)
    {
        w = max(w / compress, 1);
        h = max(h / compress, 1);
    }
    if(canreduce && texreduce)
    {
        w = max(w >> texreduce, 1);
        h = max(h >> texreduce, 1);
    }
    w = min(w, sizelimit);
    h = min(h, sizelimit);
    if(!usenp2 && (w&(w - 1) || h&(h - 1)))
    {
        tw = th = 1;
        while(tw < w) tw *= 2;
        while(th < h) th *= 2;
        if(w < tw - tw / 4) tw /= 2;
        if(h < th - th / 4) th /= 2;
    }
    else
    {
        tw = w;
        th = h;
    }
}

static inline void reorienttexture(uchar *src, int sw, int sh, int bpp, int stride, uchar *dst, bool flipx, bool flipy, bool swapxy, bool normals = false)
{
    int stridex = bpp, stridey = bpp;
    if(swapxy) stridex *= sh; else stridey *= sw;
    if(flipx) { dst += (sw - 1)*stridex; stridex = -stridex; }
    if(flipy) { dst += (sh - 1)*stridey; stridey = -stridey; }
    uchar *srcrow = src;
    loopi(sh)
    {
        for(uchar *curdst = dst, *src = srcrow, *end = &srcrow[sw*bpp]; src < end;)
        {
            loopk(bpp) curdst[k] = *src++;
            if(normals)
            {
                if(flipx) curdst[0] = 255 - curdst[0];
                if(flipy) curdst[1] = 255 - curdst[1];
                if(swapxy) swap(curdst[0], curdst[1]);
            }
            curdst += stridex;
        }
        srcrow += stride;
        dst += stridey;
    }
}

static void reorients3tc(GLenum format, int blocksize, int w, int h, uchar *src, uchar *dst, bool flipx, bool flipy, bool swapxy, bool normals = false)
{
    int bx1 = 0, by1 = 0, bx2 = min(w, 4), by2 = min(h, 4), bw = (w + 3) / 4, bh = (h + 3) / 4, stridex = blocksize, stridey = blocksize;
    if(swapxy) stridex *= bw; else stridey *= bh;
    if(flipx) { dst += (bw - 1)*stridex; stridex = -stridex; bx1 += 4 - bx2; bx2 = 4; }
    if(flipy) { dst += (bh - 1)*stridey; stridey = -stridey; by1 += 4 - by2; by2 = 4; }
    loopi(bh)
    {
        for(uchar *curdst = dst, *end = &src[bw*blocksize]; src < end; src += blocksize, curdst += stridex)
        {
            if(format == GL_COMPRESSED_RGBA_S3TC_DXT3_EXT)
            {
                ullong salpha = lilswap(*(const ullong *)src), dalpha = 0;
                uint xmask = flipx ? 15 : 0, ymask = flipy ? 15 : 0, xshift = 2, yshift = 4;
                if(swapxy) swap(xshift, yshift);
                for(int y = by1; y < by2; y++) for(int x = bx1; x < bx2; x++)
                {
                    dalpha |= ((salpha & 15) << (((xmask^x) << xshift) + ((ymask^y) << yshift)));
                    salpha >>= 4;
                }
                *(ullong *)curdst = lilswap(dalpha);
                src += 8;
                curdst += 8;
            }
            else if(format == GL_COMPRESSED_RGBA_S3TC_DXT5_EXT)
            {
                uchar alpha1 = src[0], alpha2 = src[1];
                ullong salpha = lilswap(*(const ushort *)&src[2]) + ((ullong)lilswap(*(const uint *)&src[4]) << 16), dalpha = 0;
                uint xmask = flipx ? 7 : 0, ymask = flipy ? 7 : 0, xshift = 0, yshift = 2;
                if(swapxy) swap(xshift, yshift);
                for(int y = by1; y < by2; y++) for(int x = bx1; x < bx2; x++)
                {
                    dalpha |= ((salpha & 7) << (3 * ((xmask^x) << xshift) + ((ymask^y) << yshift)));
                    salpha >>= 3;
                }
                curdst[0] = alpha1;
                curdst[1] = alpha2;
                *(ushort *)&curdst[2] = lilswap(ushort(dalpha));
                *(ushort *)&curdst[4] = lilswap(ushort(dalpha >> 16));
                *(ushort *)&curdst[6] = lilswap(ushort(dalpha >> 32));
                src += 8;
                curdst += 8;
            }

            ushort color1 = lilswap(*(const ushort *)src), color2 = lilswap(*(const ushort *)&src[2]);
            uint sbits = lilswap(*(const uint *)&src[4]);
            if(normals)
            {
                ushort ncolor1 = color1, ncolor2 = color2;
                if(flipx)
                {
                    ncolor1 = (ncolor1 & ~0xF800) | (0xF800 - (ncolor1 & 0xF800));
                    ncolor2 = (ncolor2 & ~0xF800) | (0xF800 - (ncolor2 & 0xF800));
                }
                if(flipy)
                {
                    ncolor1 = (ncolor1 & ~0x7E0) | (0x7E0 - (ncolor1 & 0x7E0));
                    ncolor2 = (ncolor2 & ~0x7E0) | (0x7E0 - (ncolor2 & 0x7E0));
                }
                if(swapxy)
                {
                    ncolor1 = (ncolor1 & 0x1F) | (((((ncolor1 >> 11) & 0x1F) * 0x3F) / 0x1F) << 5) | (((((ncolor1 >> 5) & 0x3F) * 0x1F) / 0x3F) << 11);
                    ncolor2 = (ncolor2 & 0x1F) | (((((ncolor2 >> 11) & 0x1F) * 0x3F) / 0x1F) << 5) | (((((ncolor2 >> 5) & 0x3F) * 0x1F) / 0x3F) << 11);
                }
                if(color1 <= color2 && ncolor1 > ncolor2) { color1 = ncolor2; color2 = ncolor1; }
                else { color1 = ncolor1; color2 = ncolor2; }
            }
            uint dbits = 0, xmask = flipx ? 3 : 0, ymask = flipy ? 3 : 0, xshift = 1, yshift = 3;
            if(swapxy) swap(xshift, yshift);
            for(int y = by1; y < by2; y++) for(int x = bx1; x < bx2; x++)
            {
                dbits |= ((sbits & 3) << (((xmask^x) << xshift) + ((ymask^y) << yshift)));
                sbits >>= 2;
            }
            *(ushort *)curdst = lilswap(color1);
            *(ushort *)&curdst[2] = lilswap(color2);
            *(uint *)&curdst[4] = lilswap(dbits);

            if(blocksize > 8) { src -= 8; curdst -= 8; }
        }
        dst += stridey;
    }
}

/// @param isnormalmap specifies whether you pass in a normal map and hence need to shift the blue/red channels accordingly.
void texreorient(ImageData &s, bool flipx, bool flipy, bool swapxy, bool isnormalmap)
{
    ImageData d(swapxy ? s.h : s.w, swapxy ? s.w : s.h, s.bpp, s.levels, s.align, s.compressed);
    switch(s.compressed)
    {
    case GL_COMPRESSED_RGB_S3TC_DXT1_EXT:
    case GL_COMPRESSED_RGBA_S3TC_DXT1_EXT:
    case GL_COMPRESSED_RGBA_S3TC_DXT3_EXT:
    case GL_COMPRESSED_RGBA_S3TC_DXT5_EXT:
    {
        uchar *dst = d.data, *src = s.data;
        loopi(s.levels)
        {
            reorients3tc(s.compressed, s.bpp, max(s.w >> i, 1), max(s.h >> i, 1), src, dst, flipx, flipy, swapxy, isnormalmap);
            src += s.calclevelsize(i);
            dst += d.calclevelsize(i);
        }
        break;
    }
    default:
        reorienttexture(s.data, s.w, s.h, s.bpp, s.pitch, d.data, flipx, flipy, swapxy, isnormalmap);
        break;
    }
    s.replace(d);
}


/// @param isnormalmap specifies whether you pass in a normal map and hence need to shift the blue/red channels accordingly.
void texrotate(ImageData &s, int numrots, bool isnormalmap)
{
    // 1..3 rotate through 90..270 degrees, 4 flips X, 5 flips Y
    if(numrots >= 1 && numrots <= 5)
        texreorient(s,
        numrots >= 2 && numrots <= 4, // flip X on 180/270 degrees
        numrots <= 2 || numrots == 5, // flip Y on 90/180 degrees
        (numrots & 5) == 1,           // swap X/Y on 90/270 degrees
        isnormalmap);
}

void texoffset(ImageData &s, int xoffset, int yoffset)
{
    xoffset = max(xoffset, 0);
    xoffset %= s.w;
    yoffset = max(yoffset, 0);
    yoffset %= s.h;
    if(!xoffset && !yoffset) return;
    ImageData d(s.w, s.h, s.bpp);
    uchar *src = s.data;
    loop(y, s.h)
    {
        uchar *dst = (uchar *)d.data + ((y + yoffset) % d.h)*d.pitch;
        memcpy(dst + xoffset*s.bpp, src, (s.w - xoffset)*s.bpp);
        memcpy(dst, src + (s.w - xoffset)*s.bpp, xoffset*s.bpp);
        src += s.pitch;
    }
    s.replace(d);
}

void texmad(ImageData &s, const vec &mul, const vec &add)
{
    int maxk = min(int(s.bpp), 3);
    writetex(s,
        loopk(maxk) dst[k] = uchar(clamp(dst[k] * mul[k] + 255 * add[k], 0.0f, 255.0f));
    );
}

void texcolorify(ImageData &s, const vec &color, vec weights)
{
    if(s.bpp < 3) return;
    if(weights.iszero()) weights = vec(0.21f, 0.72f, 0.07f);
    writetex(s,
        float lum = dst[0] * weights.x + dst[1] * weights.y + dst[2] * weights.z;
    loopk(3) dst[k] = uchar(clamp(lum*color[k], 0.0f, 255.0f));
    );
}

void texcolormask(ImageData &s, const vec &color1, const vec &color2)
{
    if(s.bpp < 4) return;
    ImageData d(s.w, s.h, 3);
    readwritetex(d, s,
        vec color;
    color.lerp(color2, color1, src[3] / 255.0f);
    loopk(3) dst[k] = uchar(clamp(color[k] * src[k], 0.0f, 255.0f));
    );
    s.replace(d);
}

void texdup(ImageData &s, int srcchan, int dstchan)
{
    if(srcchan == dstchan || max(srcchan, dstchan) >= s.bpp) return;
    writetex(s, dst[dstchan] = dst[srcchan]);
}

void texmix(ImageData &s, int c1, int c2, int c3, int c4)
{
    int numchans = c1 < 0 ? 0 : (c2 < 0 ? 1 : (c3 < 0 ? 2 : (c4 < 0 ? 3 : 4)));
    if(numchans <= 0) return;
    ImageData d(s.w, s.h, numchans);
    readwritetex(d, s,
        switch(numchans)
    {
        case 4: dst[3] = src[c4];
        case 3: dst[2] = src[c3];
        case 2: dst[1] = src[c2];
        case 1: dst[0] = src[c1];
    }
    );
    s.replace(d);
}

void texgrey(ImageData &s)
{
    if(s.bpp <= 2) return;
    ImageData d(s.w, s.h, s.bpp >= 4 ? 2 : 1);
    if(s.bpp >= 4)
    {
        readwritetex(d, s,
            dst[0] = src[0];
        dst[1] = src[3];
        );
    }
    else
    {
        readwritetex(d, s, dst[0] = src[0]);
    }
    s.replace(d);
}

void texpremul(ImageData &s)
{
    switch(s.bpp)
    {
    case 2:
        writetex(s,
            dst[0] = uchar((uint(dst[0])*uint(dst[1])) / 255);
        );
        break;
    case 4:
        writetex(s,
            uint alpha = dst[3];
        dst[0] = uchar((uint(dst[0])*alpha) / 255);
        dst[1] = uchar((uint(dst[1])*alpha) / 255);
        dst[2] = uchar((uint(dst[2])*alpha) / 255);
        );
        break;
    }
}

void texagrad(ImageData &s, float x2, float y2, float x1, float y1)
{
    if(s.bpp != 2 && s.bpp != 4) return;
    y1 = 1 - y1;
    y2 = 1 - y2;
    float minx = 1, miny = 1, maxx = 1, maxy = 1;
    if(x1 != x2)
    {
        minx = (0 - x1) / (x2 - x1);
        maxx = (1 - x1) / (x2 - x1);
    }
    if(y1 != y2)
    {
        miny = (0 - y1) / (y2 - y1);
        maxy = (1 - y1) / (y2 - y1);
    }
    float dx = (maxx - minx) / max(s.w - 1, 1),
        dy = (maxy - miny) / max(s.h - 1, 1),
        cury = miny;
    for(uchar *dstrow = s.data + s.bpp - 1, *endrow = dstrow + s.h*s.pitch; dstrow < endrow; dstrow += s.pitch)
    {
        float curx = minx;
        for(uchar *dst = dstrow, *end = &dstrow[s.w*s.bpp]; dst < end; dst += s.bpp)
        {
            dst[0] = uchar(dst[0] * clamp(curx, 0.0f, 1.0f)*clamp(cury, 0.0f, 1.0f));
            curx += dx;
        }
        cury += dy;
    }
}


void texflip(ImageData &s)
{
    ImageData d(s.w, s.h, s.bpp);
    uchar *dst = d.data, *src = &s.data[s.pitch*s.h];
    loopi(s.h)
    {
        src -= s.pitch;
        memcpy(dst, src, s.bpp*s.w);
        dst += d.pitch;
    }
    s.replace(d);
}

void texnormal(ImageData &s, int emphasis)
{
    ImageData d(s.w, s.h, 3);
    uchar *src = s.data, *dst = d.data;
    loop(y, s.h) loop(x, s.w)
    {
        vec normal(0.0f, 0.0f, 255.0f / emphasis);
        normal.x += src[y*s.pitch + ((x + s.w - 1) % s.w)*s.bpp];
        normal.x -= src[y*s.pitch + ((x + 1) % s.w)*s.bpp];
        normal.y += src[((y + s.h - 1) % s.h)*s.pitch + x*s.bpp];
        normal.y -= src[((y + 1) % s.h)*s.pitch + x*s.bpp];
        normal.normalize();
        *dst++ = uchar(127.5f + normal.x*127.5f);
        *dst++ = uchar(127.5f + normal.y*127.5f);
        *dst++ = uchar(127.5f + normal.z*127.5f);
    }
    s.replace(d);
}

template<int n, int bpp, bool normals>
static void blurtexture(int w, int h, uchar *dst, const uchar *src, int margin)
{
    static const int weights3x3[9] =
    {
        0x10, 0x20, 0x10,
        0x20, 0x40, 0x20,
        0x10, 0x20, 0x10
    };
    static const int weights5x5[25] =
    {
        0x05, 0x05, 0x09, 0x05, 0x05,
        0x05, 0x0A, 0x14, 0x0A, 0x05,
        0x09, 0x14, 0x28, 0x14, 0x09,
        0x05, 0x0A, 0x14, 0x0A, 0x05,
        0x05, 0x05, 0x09, 0x05, 0x05
    };
    const int *mat = n > 1 ? weights5x5 : weights3x3;
    int mstride = 2 * n + 1,
        mstartoffset = n*(mstride + 1),
        stride = bpp*w,
        startoffset = n*bpp,
        nextoffset1 = stride + mstride*bpp,
        nextoffset2 = stride - mstride*bpp;
    src += margin*(stride + bpp);
    for(int y = margin; y < h - margin; y++)
    {
        for(int x = margin; x < w - margin; x++)
        {
            int dr = 0, dg = 0, db = 0;
            const uchar *p = src - startoffset;
            const int *m = mat + mstartoffset;
            for(int t = y; t >= y - n; t--, p -= nextoffset1, m -= mstride)
            {
                if(t < 0) p += stride;
                int a = 0;
                if(n > 1) { a += m[-2]; if(x >= 2) { dr += p[0] * a; dg += p[1] * a; db += p[2] * a; a = 0; } p += bpp; }
                a += m[-1]; if(x >= 1) { dr += p[0] * a; dg += p[1] * a; db += p[2] * a; a = 0; } p += bpp;
                int cr = p[0], cg = p[1], cb = p[2]; a += m[0]; dr += cr * a; dg += cg * a; db += cb * a; p += bpp;
                if(x + 1 < w) { cr = p[0]; cg = p[1]; cb = p[2]; } dr += cr * m[1]; dg += cg * m[1]; db += cb * m[1]; p += bpp;
                if(n > 1) { if(x + 2 < w) { cr = p[0]; cg = p[1]; cb = p[2]; } dr += cr * m[2]; dg += cg * m[2]; db += cb * m[2]; p += bpp; }
            }
            p = src - startoffset + stride;
            m = mat + mstartoffset + mstride;
            for(int t = y + 1; t <= y + n; t++, p += nextoffset2, m += mstride)
            {
                if(t >= h) p -= stride;
                int a = 0;
                if(n > 1) { a += m[-2]; if(x >= 2) { dr += p[0] * a; dg += p[1] * a; db += p[2] * a; a = 0; } p += bpp; }
                a += m[-1]; if(x >= 1) { dr += p[0] * a; dg += p[1] * a; db += p[2] * a; a = 0; } p += bpp;
                int cr = p[0], cg = p[1], cb = p[2]; a += m[0]; dr += cr * a; dg += cg * a; db += cb * a; p += bpp;
                if(x + 1 < w) { cr = p[0]; cg = p[1]; cb = p[2]; } dr += cr * m[1]; dg += cg * m[1]; db += cb * m[1]; p += bpp;
                if(n > 1) { if(x + 2 < w) { cr = p[0]; cg = p[1]; cb = p[2]; } dr += cr * m[2]; dg += cg * m[2]; db += cb * m[2]; p += bpp; }
            }
            if(normals)
            {
                vec v(dr - 0x7F80, dg - 0x7F80, db - 0x7F80);
                float mag = 127.5f / v.magnitude();
                dst[0] = uchar(v.x*mag + 127.5f);
                dst[1] = uchar(v.y*mag + 127.5f);
                dst[2] = uchar(v.z*mag + 127.5f);
            }
            else
            {
                dst[0] = dr >> 8;
                dst[1] = dg >> 8;
                dst[2] = db >> 8;
            }
            if(bpp > 3) dst[3] = src[3];
            dst += bpp;
            src += bpp;
        }
        src += 2 * margin*bpp;
    }
}

void blurtexture(int n, int bpp, int w, int h, uchar *dst, const uchar *src, int margin)
{
    switch((clamp(n, 1, 2) << 4) | bpp)
    {
    case 0x13: blurtexture<1, 3, false>(w, h, dst, src, margin); break;
    case 0x23: blurtexture<2, 3, false>(w, h, dst, src, margin); break;
    case 0x14: blurtexture<1, 4, false>(w, h, dst, src, margin); break;
    case 0x24: blurtexture<2, 4, false>(w, h, dst, src, margin); break;
    }
}

void blurnormals(int n, int w, int h, bvec *dst, const bvec *src, int margin)
{
    switch(clamp(n, 1, 2))
    {
    case 1: blurtexture<1, 3, true>(w, h, dst->v, src->v, margin); break;
    case 2: blurtexture<2, 3, true>(w, h, dst->v, src->v, margin); break;
    }
}

void texblur(ImageData &s, int n, int r)
{
    if(s.bpp < 3) return;
    loopi(r)
    {
        ImageData d(s.w, s.h, s.bpp);
        blurtexture(n, s.bpp, s.w, s.h, d.data, s.data);
        s.replace(d);
    }
}

void forcergbimage(ImageData &s)
{
    if(s.bpp >= 3) return;
    ImageData d(s.w, s.h, 3);
    readwritetex(d, s,
        switch(s.bpp)
    {
        case 1: dst[0] = src[0]; dst[1] = src[0]; dst[2] = src[0]; break;
        case 2: dst[0] = src[0]; dst[1] = src[1]; dst[2] = src[1]; break;
    }
    );
    s.replace(d);
}

void scaleimage(ImageData &s, int w, int h)
{
    ImageData d(w, h, s.bpp);
    scaletexture(s.data, s.w, s.h, s.bpp, s.pitch, d.data, w, h);
    s.replace(d);
}
