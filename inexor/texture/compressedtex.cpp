/// @file compressed texture (mostly dds) loading.

#include "inexor/texture/compressedtex.hpp"
#include "inexor/util/Logging.hpp"

VAR(dbgdds, 0, 0, 1);

#define DECODEDDS(name, dbpp, initblock, writeval, nextval) \
static void name(ImageData &s) \
{ \
    ImageData d(s.w, s.h, dbpp); \
    uchar *dst = d.data; \
    const uchar *src = s.data; \
    for(int by = 0; by < s.h; by += s.align) \
        { \
        for(int bx = 0; bx < s.w; bx += s.align, src += s.bpp) \
                { \
            int maxy = min(d.h - by, s.align), maxx = min(d.w - bx, s.align); \
            initblock; \
            loop(y, maxy) \
            { \
                int x; \
                for(x = 0; x < maxx; ++x) \
                                { \
                    writeval; \
                    nextval; \
                    dst += d.bpp; \
                                }  \
                for(; x < s.align; ++x) { nextval; } \
                dst += d.pitch - maxx*d.bpp; \
            } \
            dst += maxx*d.bpp - maxy*d.pitch; \
                } \
        dst += (s.align-1)*d.pitch; \
        } \
    s.replace(d); \
}

DECODEDDS(decodedxt1, s.compressed == GL_COMPRESSED_RGBA_S3TC_DXT1_EXT ? 4 : 3,
    ushort color0 = lilswap(*(const ushort *)src);
ushort color1 = lilswap(*(const ushort *)&src[2]);
uint bits = lilswap(*(const uint *)&src[4]);
bvec4 rgba[4];
rgba[0] = bvec4(bvec::from565(color0), 0xFF);
rgba[1] = bvec4(bvec::from565(color1), 0xFF);
if(color0 > color1)
{
    rgba[2].lerp(rgba[0], rgba[1], 2, 1, 3);
    rgba[3].lerp(rgba[0], rgba[1], 1, 2, 3);
}
else
{
    rgba[2].lerp(rgba[0], rgba[1], 1, 1, 2);
    rgba[3] = bvec4(0, 0, 0, 0);
}
,
memcpy(dst, rgba[bits & 3].v, d.bpp);
,
bits >>= 2;
);

DECODEDDS(decodedxt3, 4,
    ullong alpha = lilswap(*(const ullong *)src);
ushort color0 = lilswap(*(const ushort *)&src[8]);
ushort color1 = lilswap(*(const ushort *)&src[10]);
uint bits = lilswap(*(const uint *)&src[12]);
bvec rgb[4];
rgb[0] = bvec::from565(color0);
rgb[1] = bvec::from565(color1);
rgb[2].lerp(rgb[0], rgb[1], 2, 1, 3);
rgb[3].lerp(rgb[0], rgb[1], 1, 2, 3);
,
memcpy(dst, rgb[bits & 3].v, 3);
dst[3] = ((alpha & 0xF) * 1088 + 32) >> 6;
,
bits >>= 2;
alpha >>= 4;
);

static inline void decodealpha(uchar alpha0, uchar alpha1, uchar alpha[8])
{
    alpha[0] = alpha0;
    alpha[1] = alpha1;
    if(alpha0 > alpha1)
    {
        alpha[2] = (6 * alpha0 + alpha1) / 7;
        alpha[3] = (5 * alpha0 + 2 * alpha1) / 7;
        alpha[4] = (4 * alpha0 + 3 * alpha1) / 7;
        alpha[5] = (3 * alpha0 + 4 * alpha1) / 7;
        alpha[6] = (2 * alpha0 + 5 * alpha1) / 7;
        alpha[7] = (alpha0 + 6 * alpha1) / 7;
    }
    else
    {
        alpha[2] = (4 * alpha0 + alpha1) / 5;
        alpha[3] = (3 * alpha0 + 2 * alpha1) / 5;
        alpha[4] = (2 * alpha0 + 3 * alpha1) / 5;
        alpha[5] = (alpha0 + 4 * alpha1) / 5;
        alpha[6] = 0;
        alpha[7] = 0xFF;
    }
}

DECODEDDS(decodedxt5, 4,
    uchar alpha[8];
decodealpha(src[0], src[1], alpha);
ullong alphabits = lilswap(*(const ushort *)&src[2]) + ((ullong)lilswap(*(const uint *)&src[4]) << 16);
ushort color0 = lilswap(*(const ushort *)&src[8]);
ushort color1 = lilswap(*(const ushort *)&src[10]);
uint bits = lilswap(*(const uint *)&src[12]);
bvec rgb[4];
rgb[0] = bvec::from565(color0);
rgb[1] = bvec::from565(color1);
rgb[2].lerp(rgb[0], rgb[1], 2, 1, 3);
rgb[3].lerp(rgb[0], rgb[1], 1, 2, 3);
,
memcpy(dst, rgb[bits & 3].v, 3);
dst[3] = alpha[alphabits & 7];
,
bits >>= 2;
alphabits >>= 3;
);

bool loaddds(const char *filename, ImageData &image, int force)
{
    stream *f = openfile(filename, "rb");
    if(!f) return false;
    GLenum format = GL_FALSE;
    uchar magic[4];
    if(f->read(magic, 4) != 4 || memcmp(magic, "DDS ", 4)) { delete f; return false; }
    DDSURFACEDESC2 d;
    if(f->read(&d, sizeof(d)) != sizeof(d)) { delete f; return false; }
    lilswap((uint *)&d, sizeof(d) / sizeof(uint));
    if(d.dwSize != sizeof(DDSURFACEDESC2) || d.ddpfPixelFormat.dwSize != sizeof(DDPIXELFORMAT)) { delete f; return false; }
    bool supported = false;
    if(d.ddpfPixelFormat.dwFlags & DDPF_FOURCC)
    {
        switch(d.ddpfPixelFormat.dwFourCC)
        {
        case FOURCC_DXT1:
            if((supported = hasS3TC) || force) format = d.ddpfPixelFormat.dwFlags & DDPF_ALPHAPIXELS ? GL_COMPRESSED_RGBA_S3TC_DXT1_EXT : GL_COMPRESSED_RGB_S3TC_DXT1_EXT;
            break;
        case FOURCC_DXT2:
        case FOURCC_DXT3:
            if((supported = hasS3TC) || force) format = GL_COMPRESSED_RGBA_S3TC_DXT3_EXT;
            break;
        case FOURCC_DXT4:
        case FOURCC_DXT5:
            if((supported = hasS3TC) || force) format = GL_COMPRESSED_RGBA_S3TC_DXT5_EXT;
            break;
        }
    }
    if(!format || (!supported && !force)) { delete f; return false; }
    if(dbgdds) Log.default->debug("{0}: format {1}, {2} x {3}, {4} mipmaps", filename, format, d.dwWidth, d.dwHeight, d.dwMipMapCount);
    int bpp = 0;
    switch(format)
    {
    case GL_COMPRESSED_RGB_S3TC_DXT1_EXT:
    case GL_COMPRESSED_RGBA_S3TC_DXT1_EXT: bpp = 8; break;
    case GL_COMPRESSED_RGBA_S3TC_DXT3_EXT:
    case GL_COMPRESSED_RGBA_S3TC_DXT5_EXT: bpp = 16; break;
    }
    image.setdata(NULL, d.dwWidth, d.dwHeight, bpp, !supported || force > 0 ? 1 : d.dwMipMapCount, 4, format);
    size_t size = image.calcsize();
    if(f->read(image.data, size) != size) { delete f; image.cleanup(); return false; }
    delete f;
    if(!supported || force > 0) switch(format)
    {
    case GL_COMPRESSED_RGB_S3TC_DXT1_EXT:
    case GL_COMPRESSED_RGBA_S3TC_DXT1_EXT:
        decodedxt1(image);
        break;
    case GL_COMPRESSED_RGBA_S3TC_DXT3_EXT:
        decodedxt3(image);
        break;
    case GL_COMPRESSED_RGBA_S3TC_DXT5_EXT:
        decodedxt5(image);
        break;
    }
    return true;
}
