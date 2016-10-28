/// @file environment map loading routine.

#include "inexor/texture/cubemap.hpp"
#include "inexor/texture/image.hpp"
#include "inexor/texture/format.hpp"
#include "inexor/filesystem/mediadirs.hpp"
#include "inexor/ui/screen/ScreenManager.hpp"
#include "inexor/util/Logging.hpp"

namespace inexor {
namespace ui {
namespace screen {
    extern ScreenManager screen_manager;
}
}
}

using namespace inexor::ui::screen;

void forcecubemapload(GLuint tex)
{
    extern SharedVar<int> ati_cubemap_bug;
    if(!ati_cubemap_bug || !tex) return;

    SETSHADER(cubemap);
    GLenum depthtest = glIsEnabled(GL_DEPTH_TEST), blend = glIsEnabled(GL_BLEND);
    if(depthtest) glDisable(GL_DEPTH_TEST);
    glBindTexture(GL_TEXTURE_CUBE_MAP, tex);
    if(!blend) glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    gle::defvertex(2);
    gle::deftexcoord0(3);
    gle::defcolor(4);
    gle::begin(GL_LINES);
    loopi(2)
    {
        gle::attribf(i*1e-3f, 0);
        gle::attribf(0, 0, 1);
        gle::attribf(1, 1, 1, 0);
    }
    gle::end();
    if(!blend) glDisable(GL_BLEND);
    if(depthtest) glEnable(GL_DEPTH_TEST);
}

cubemapside cubemapsides[6] =
{
    { GL_TEXTURE_CUBE_MAP_NEGATIVE_X, "lf", true,  true,  true },
    { GL_TEXTURE_CUBE_MAP_POSITIVE_X, "rt", false, false, true },
    { GL_TEXTURE_CUBE_MAP_NEGATIVE_Y, "ft", true,  false, false },
    { GL_TEXTURE_CUBE_MAP_POSITIVE_Y, "bk", false, true,  false },
    { GL_TEXTURE_CUBE_MAP_NEGATIVE_Z, "dn", false, false, true },
    { GL_TEXTURE_CUBE_MAP_POSITIVE_Z, "up", false, false, true },
};

VARFP(envmapsize, 4, 7, 10, setupmaterials());

Texture *cubemaploadwildcard(Texture *t, const char *name, bool mipit, bool msg, bool transient)
{
    string tname;
    if(!name) copystring(tname, t->name);
    else
    {
        t = gettexture(tname);
        if(t)
        {
            if(!transient && t->type&Texture::TRANSIENT) t->type &= ~Texture::TRANSIENT;
            return t;
        }
    }
    char *wildcard = strchr(tname, '*');
    ImageData surface[6];
    string sname;
    if(!wildcard) copystring(sname, tname);
    int tsize = 0, compress = 0;
    loopi(6)
    {
        if(wildcard)
        {
            copystring(sname, stringslice(tname, wildcard));
            concatstring(sname, cubemapsides[i].name);
            concatstring(sname, wildcard + 1);
        }
        ImageData &s = surface[i];
        texturedata(s, sname, NULL, msg, &compress);
        if(!s.data) return NULL;
        if(s.w != s.h)
        {
            if(msg) spdlog::get("global")->error() << "cubemap texture " << sname << " does not have square size";
            return NULL;
        }
        if(s.compressed ? s.compressed != surface[0].compressed || s.w != surface[0].w || s.h != surface[0].h || s.levels != surface[0].levels : surface[0].compressed || s.bpp != surface[0].bpp)
        {
            if(msg) spdlog::get("global")->error() << "cubemap texture " << sname << " doesn't match other sides' format";
            return NULL;
        }
        tsize = max(tsize, max(s.w, s.h));
    }
    if(name)
    {
        t = registertexture(tname);
    }
    t->type = Texture::CUBEMAP;
    if(transient) t->type |= Texture::TRANSIENT;
    GLenum format;
    if(surface[0].compressed)
    {
        format = uncompressedformat(surface[0].compressed);
        t->bpp = formatsize(format);
        t->type |= Texture::COMPRESSED;
    }
    else
    {
        format = texformat(surface[0].bpp);
        t->bpp = surface[0].bpp;
    }
    if(alphaformat(format)) t->type |= Texture::ALPHA;
    t->mipmap = mipit;
    t->clamp = 3;
    t->xs = t->ys = tsize;
    t->w = t->h = min(1 << envmapsize, tsize);
    resizetexture(t->w, t->h, mipit, false, GL_TEXTURE_CUBE_MAP, compress, t->w, t->h);
    GLenum component = format;
    if(!surface[0].compressed)
    {
        component = compressedformat(format, t->w, t->h, compress);
        switch(component)
        {
        case GL_RGB: component = GL_RGB5; break;
        }
    }
    glGenTextures(1, &t->id);
    loopi(6)
    {
        ImageData &s = surface[i];
        cubemapside &side = cubemapsides[i];
        texreorient(s, side.flipx, side.flipy, side.swapxy);
        if(s.compressed)
        {
            int w = s.w, h = s.h, levels = s.levels, level = 0;
            uchar *data = s.data;
            while(levels > 1 && (w > t->w || h > t->h))
            {
                data += s.calclevelsize(level++);
                levels--;
                if(w > 1) w /= 2;
                if(h > 1) h /= 2;
            }
            createcompressedtexture(!i ? t->id : 0, w, h, data, s.align, s.bpp, levels, 3, mipit ? 2 : 1, s.compressed, side.target);
        }
        else
        {
            createtexture(!i ? t->id : 0, t->w, t->h, s.data, 3, mipit ? 2 : 1, component, side.target, s.w, s.h, s.pitch, false, format);
        }
    }
    forcecubemapload(t->id);
    return t;
}

Texture *cubemapload(const char *name, bool mipit, bool msg, bool transient)
{
    string pname;
    inexor::filesystem::getmediapath(pname, MAXSTRLEN, name, DIR_SKYBOX);

    Texture *t = NULL;
    if(!strchr(pname, '*'))
    {
        defformatstring(jpgname, "%s_*.jpg", pname);
        t = cubemaploadwildcard(NULL, jpgname, mipit, false, transient);
        if(!t)
        {
            defformatstring(pngname, "%s_*.png", pname);
            t = cubemaploadwildcard(NULL, pngname, mipit, false, transient);
            if(!t && msg) spdlog::get("global")->error() << "could not load envmap " << name;
        }
    }
    else t = cubemaploadwildcard(NULL, pname, mipit, msg, transient);
    return t;
}

VAR(envmapradius, 0, 128, 10000);

struct envmap
{
    int radius, size, blur;
    vec o;
    GLuint tex;
};

static vector<envmap> envmaps;
static Texture *skyenvmap = NULL;

void clearenvmaps()
{
    if(skyenvmap)
    {
        if(skyenvmap->type&Texture::TRANSIENT) cleanuptexture(skyenvmap);
        skyenvmap = NULL;
    }
    loopv(envmaps) glDeleteTextures(1, &envmaps[i].tex);
    envmaps.shrink(0);
}

VAR(aaenvmap, 0, 2, 4);

GLuint genenvmap(const vec &o, int envmapsize, int blur)
{
    int rendersize = 1 << (envmapsize + aaenvmap), sizelimit = min(hwcubetexsize, min(screen_manager.screenw, screen_manager.screenh));
    if(maxtexsize) sizelimit = min(sizelimit, maxtexsize);
    while(rendersize > sizelimit) rendersize /= 2;
    int texsize = min(rendersize, 1 << envmapsize);
    if(!aaenvmap) rendersize = texsize;
    GLuint tex;
    glGenTextures(1, &tex);
    glViewport(0, 0, rendersize, rendersize);
    float yaw = 0, pitch = 0;
    uchar *pixels = new uchar[3 * rendersize*rendersize * 2];
    glPixelStorei(GL_PACK_ALIGNMENT, texalign(pixels, rendersize, 3));
    loopi(6)
    {
        const cubemapside &side = cubemapsides[i];
        switch(side.target)
        {
            case GL_TEXTURE_CUBE_MAP_NEGATIVE_X: // lf
                yaw = 90; pitch = 0; break;
            case GL_TEXTURE_CUBE_MAP_POSITIVE_X: // rt
                yaw = 270; pitch = 0; break;
            case GL_TEXTURE_CUBE_MAP_NEGATIVE_Y: // ft
                yaw = 180; pitch = 0; break;
            case GL_TEXTURE_CUBE_MAP_POSITIVE_Y: // bk
                yaw = 0; pitch = 0; break;
            case GL_TEXTURE_CUBE_MAP_NEGATIVE_Z: // dn
                yaw = 270; pitch = -90; break;
            case GL_TEXTURE_CUBE_MAP_POSITIVE_Z: // up
                yaw = 270; pitch = 90; break;
        }
        glFrontFace((side.flipx == side.flipy) != side.swapxy ? GL_CW : GL_CCW);
        drawcubemap(rendersize, o, yaw, pitch, side);
        uchar *src = pixels, *dst = &pixels[3 * rendersize*rendersize];
        glReadPixels(0, 0, rendersize, rendersize, GL_RGB, GL_UNSIGNED_BYTE, src);
        if(rendersize > texsize)
        {
            scaletexture(src, rendersize, rendersize, 3, 3 * rendersize, dst, texsize, texsize);
            swap(src, dst);
        }
        if(blur > 0)
        {
            blurtexture(blur, 3, texsize, texsize, dst, src);
            swap(src, dst);
        }
        createtexture(tex, texsize, texsize, src, 3, 2, GL_RGB5, side.target);
    }
    glFrontFace(GL_CW);
    glViewport(0, 0, screen_manager.screenw, screen_manager.screenh);
    delete[] pixels;
    clientkeepalive(); // todo threadsafe
    forcecubemapload(tex);
    return tex;
}

void initenvmaps()
{
    clearenvmaps();
    extern SharedVar<char *> skybox;
    char *da = *skybox; //TODO fix
    skyenvmap = da[0] ? cubemapload(da, true, false, true) : NULL;
    const vector<extentity *> &ents = entities::getents();
    loopv(ents)
    {
        const extentity &ent = *ents[i];
        if(ent.type != ET_ENVMAP) continue;
        envmap &em = envmaps.add();
        em.radius = ent.attr1 ? clamp(int(ent.attr1), 0, 10000) : envmapradius;
        em.size = ent.attr2 ? clamp(int(ent.attr2), 4, 9) : 0;
        em.blur = ent.attr3 ? clamp(int(ent.attr3), 1, 2) : 0;
        em.o = ent.o;
        em.tex = 0;
    }
}

void genenvmaps()
{
    if(envmaps.empty()) return;
    renderprogress(0, "generating environment maps...");
    int lastprogress = SDL_GetTicks();
    loopv(envmaps)
    {
        envmap &em = envmaps[i];
        em.tex = genenvmap(em.o, em.size ? min(em.size, envmapsize) : envmapsize, em.blur);
        if(renderedframe) continue;
        int millis = SDL_GetTicks();
        if(millis - lastprogress >= 250)
        {
            renderprogress(float(i + 1) / envmaps.length(), "generating environment maps...", 0, true);
            lastprogress = millis;
        }
    }
}

ushort closestenvmap(const vec &o)
{
    ushort minemid = EMID_SKY;
    float mindist = 1e16f;
    loopv(envmaps)
    {
        envmap &em = envmaps[i];
        float dist = em.o.dist(o);
        if(dist < em.radius && dist < mindist)
        {
            minemid = EMID_RESERVED + i;
            mindist = dist;
        }
    }
    return minemid;
}

ushort closestenvmap(int orient, const ivec &co, int size)
{
    vec loc(co);
    int dim = dimension(orient);
    if(dimcoord(orient)) loc[dim] += size;
    loc[R[dim]] += size / 2;
    loc[C[dim]] += size / 2;
    return closestenvmap(loc);
}

GLuint lookupenvmap(Slot &slot)
{
    loopv(slot.sts) if(slot.sts[i].type == TEX_ENVMAP && slot.sts[i].t) return slot.sts[i].t->id;
    return skyenvmap ? skyenvmap->id : 0;
}

GLuint lookupenvmap(ushort emid)
{
    if(emid == EMID_SKY || emid == EMID_CUSTOM) return skyenvmap ? skyenvmap->id : 0;
    if(emid == EMID_NONE || !envmaps.inrange(emid - EMID_RESERVED)) return 0;
    GLuint tex = envmaps[emid - EMID_RESERVED].tex;
    return tex ? tex : (skyenvmap ? skyenvmap->id : 0);
}
