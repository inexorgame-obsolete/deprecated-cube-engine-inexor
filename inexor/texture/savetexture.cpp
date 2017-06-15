/// @file everything to save images of various formats.
#include "inexor/network/SharedTree.hpp"
#include "inexor/texture/savetexture.hpp"
#include "inexor/texture/SDL_loading.hpp"
#include "inexor/texture/image.hpp"
#include "inexor/ui/screen/ScreenManager.hpp"
#include "inexor/util/Logging.hpp"

using namespace inexor::rendering::screen;

void writepngchunk(stream *f, const char *type, uchar *data = NULL, uint len = 0)
{
    f->putbig<uint>(len);
    f->write(type, 4);
    f->write(data, len);

    uint crc = crc32(0, Z_NULL, 0);
    crc = crc32(crc, (const Bytef *)type, 4);
    if(data) crc = crc32(crc, data, len);
    f->putbig<uint>(crc);
}

VARP(compresspng, 0, 9, 9);

void savepng(const char *filename, ImageData &image, bool flip)
{
    uchar ctype = 0;
    switch(image.bpp)
    {
    case 1: ctype = 0; break;
    case 2: ctype = 4; break;
    case 3: ctype = 2; break;
    case 4: ctype = 6; break;
    default: spdlog::get("global")->error("failed saving png to {}", filename); return;
    }
    stream *f = openfile(filename, "wb");
    if(!f) { spdlog::get("global")->error("could not write to {}", filename); return; }

    uchar signature[] = { 137, 80, 78, 71, 13, 10, 26, 10 };
    f->write(signature, sizeof(signature));

    struct pngihdr
    {
        uint width, height;
        uchar bitdepth, colortype, compress, filter, interlace;
    } ihdr = { bigswap<uint>(image.w), bigswap<uint>(image.h), 8, ctype, 0, 0, 0 };
    writepngchunk(f, "IHDR", (uchar *)&ihdr, 13);

    stream::offset idat = f->tell();
    uint len = 0;
    f->write("\0\0\0\0IDAT", 8);
    uint crc = crc32(0, Z_NULL, 0);
    crc = crc32(crc, (const Bytef *)"IDAT", 4);

    z_stream z;
    z.zalloc = NULL;
    z.zfree = NULL;
    z.opaque = NULL;

    if(deflateInit(&z, compresspng) != Z_OK)
        goto error;

    uchar buf[1 << 12];
    z.next_out = (Bytef *)buf;
    z.avail_out = sizeof(buf);

    loopi(image.h)
    {
        uchar filter = 0;
        loopj(2)
        {
            z.next_in = j ? (Bytef *)image.data + (flip ? image.h - i - 1 : i)*image.pitch : (Bytef *)&filter;
            z.avail_in = j ? image.w*image.bpp : 1;
            while(z.avail_in > 0)
            {
                if(deflate(&z, Z_NO_FLUSH) != Z_OK) goto cleanuperror;
#define FLUSHZ do { \
                    int flush = sizeof(buf) - z.avail_out; \
                    crc = crc32(crc, buf, flush); \
                    len += flush; \
                    f->write(buf, flush); \
                    z.next_out = (Bytef *)buf; \
                    z.avail_out = sizeof(buf); \
                                } while(0)
                FLUSHZ;
            }
        }
    }

    for(;;)
    {
        int err = deflate(&z, Z_FINISH);
        if(err != Z_OK && err != Z_STREAM_END) goto cleanuperror;
        FLUSHZ;
        if(err == Z_STREAM_END) break;
    }

    deflateEnd(&z);

    f->seek(idat, SEEK_SET);
    f->putbig<uint>(len);
    f->seek(0, SEEK_END);
    f->putbig<uint>(crc);

    writepngchunk(f, "IEND");

    delete f;
    return;

cleanuperror:
    deflateEnd(&z);

error:
    delete f;

    spdlog::get("global")->error("failed saving png to {}", filename);
}

struct tgaheader
{
    uchar  identsize;
    uchar  cmaptype;
    uchar  imagetype;
    uchar  cmaporigin[2];
    uchar  cmapsize[2];
    uchar  cmapentrysize;
    uchar  xorigin[2];
    uchar  yorigin[2];
    uchar  width[2];
    uchar  height[2];
    uchar  pixelsize;
    uchar  descbyte;
};

VARP(compresstga, 0, 1, 1);

void savetga(const char *filename, ImageData &image, bool flip)
{
    switch(image.bpp)
    {
    case 3: case 4: break;
    default: spdlog::get("global")->error("failed saving tga to {}", filename); return;
    }

    stream *f = openfile(filename, "wb");
    if(!f) { spdlog::get("global")->error("could not write to {}", filename); return; }

    tgaheader hdr;
    memset(&hdr, 0, sizeof(hdr));
    hdr.pixelsize = image.bpp * 8;
    hdr.width[0] = image.w & 0xFF;
    hdr.width[1] = (image.w >> 8) & 0xFF;
    hdr.height[0] = image.h & 0xFF;
    hdr.height[1] = (image.h >> 8) & 0xFF;
    hdr.imagetype = compresstga ? 10 : 2;
    f->write(&hdr, sizeof(hdr));

    uchar buf[128 * 4];
    loopi(image.h)
    {
        uchar *src = image.data + (flip ? i : image.h - i - 1)*image.pitch;
        for(int remaining = image.w; remaining > 0;)
        {
            int raw = 1;
            if(compresstga)
            {
                int run = 1;
                for(uchar *scan = src; run < min(remaining, 128); run++)
                {
                    scan += image.bpp;
                    if(src[0] != scan[0] || src[1] != scan[1] || src[2] != scan[2] || (image.bpp == 4 && src[3] != scan[3])) break;
                }
                if(run > 1)
                {
                    f->putchar(0x80 | (run - 1));
                    f->putchar(src[2]); f->putchar(src[1]); f->putchar(src[0]);
                    if(image.bpp == 4) f->putchar(src[3]);
                    src += run*image.bpp;
                    remaining -= run;
                    if(remaining <= 0) break;
                }
                for(uchar *scan = src; raw < min(remaining, 128); raw++)
                {
                    scan += image.bpp;
                    if(src[0] == scan[0] && src[1] == scan[1] && src[2] == scan[2] && (image.bpp != 4 || src[3] == scan[3])) break;
                }
                f->putchar(raw - 1);
            }
            else raw = min(remaining, 128);
            uchar *dst = buf;
            loopj(raw)
            {
                dst[0] = src[2];
                dst[1] = src[1];
                dst[2] = src[0];
                if(image.bpp == 4) dst[3] = src[3];
                dst += image.bpp;
                src += image.bpp;
            }
            f->write(buf, raw*image.bpp);
            remaining -= raw;
        }
    }

    delete f;
}

VARP(screenshotformat, 0, IMG_PNG, NUMIMG - 1);

const char *imageexts[NUMIMG] = { ".bmp", ".tga", ".png" };

int guessimageformat(const char *filename, int format)
{
    int len = strlen(filename);
    loopi(NUMIMG)
    {
        int extlen = strlen(imageexts[i]);
        if(len >= extlen && !strcasecmp(&filename[len - extlen], imageexts[i])) return i;
    }
    return format;
}

void saveimage(const char *filename, int format, ImageData &image, bool flip)
{
    switch(format)
    {
    case IMG_PNG: savepng(filename, image, flip); break;
    case IMG_TGA: savetga(filename, image, flip); break;
    default:
    {
        ImageData flipped(image.w, image.h, image.bpp, image.data);
        if(flip) texflip(flipped);
        SDL_Surface *s = wrapsurface(flipped.data, flipped.w, flipped.h, flipped.bpp);
        if(!s) break;
        const char *found = findfile(filename, "wb");
        if(found) SDL_SaveBMP(s, found);
        SDL_FreeSurface(s);
        break;
    }
    }
}

SVARP(screenshotdir, "screenshot");

void screenshot(char *filename)
{
    static string buf;
    int format = -1, dirlen = 0;
    copystring(buf, screenshotdir);
    if(screenshotdir[0])
    {
        dirlen = strlen(buf);
        if(buf[dirlen] != '/' && buf[dirlen] != '\\' && dirlen + 1 < (int)sizeof(buf)) { buf[dirlen] = '/'; buf[dirlen + 1] = '\0'; }
        const char *dir = findfile(buf, "w");
        if(!fileexists(dir, "w")) createdir(dir);
    }
    if(filename[0])
    {
        concatstring(buf, filename);
        format = guessimageformat(buf, -1);
    }
    else
    {
        const char *sstime = gettimestr();
        concatstring(buf, sstime);

        const char *map = game::getclientmap(), *mode = game::getclientmode();

        if(map && map[0])
        {
            concatstring(buf, "_");
            concatstring(buf, map);
        }
        if(mode && mode[0])
        {
            concatstring(buf, "_");
            concatstring(buf, mode);
        }

        for(char *s = &buf[dirlen+1]; *s; s++) if(iscubespace(*s) || *s == '/' || *s == '\\') *s = '-';
    }
    if(format < 0)
    {
        format = screenshotformat;
        concatstring(buf, imageexts[format]);
    }

    ImageData image(screen_manager.screenw, screen_manager.screenh, 3);
    glPixelStorei(GL_PACK_ALIGNMENT, texalign(image.data, screen_manager.screenw, 3));
    glReadPixels(0, 0, screen_manager.screenw, screen_manager.screenh, GL_RGB, GL_UNSIGNED_BYTE, image.data);
    saveimage(path(buf), format, image, true);
}

COMMAND(screenshot, "s");
