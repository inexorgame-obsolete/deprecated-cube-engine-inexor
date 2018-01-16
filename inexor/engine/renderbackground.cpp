
#include "inexor/engine/renderbackground.hpp"
#include "inexor/shared/geom.hpp"
#include "inexor/engine/rendertext.hpp"
#include "inexor/engine/rendergl.hpp"
#include "inexor/engine/shader.hpp"
#include "inexor/engine/frame.hpp"
#include "inexor/client/network.hpp"

#include "inexor/ui/screen/ScreenManager.hpp"
#include "inexor/ui/legacy/menus.hpp"

#include "inexor/io/filesystem/mediadirs.hpp"
#include "inexor/sound/sound.hpp"
#include "inexor/util/legacy_time.hpp"
#include "inexor/util/random.hpp"

#include "inexor/engine/glemu.hpp"
#include "inexor/shared/command.hpp"

using inexor::rendering::screen::screen_manager;
using inexor::sound::stopsounds;
using inexor::filesystem::getmediapath;
using inexor::util::rnd;

static Texture *logo_texture = nullptr;
static Texture *background_texture = nullptr;
SVARFP(background, "interface/background.png", background_texture = NULL;);
SVARFP(logo, "interface/logo.png", logo_texture = NULL;);

static Texture *mapshotframe_texture = nullptr;
static Texture *loadingbar_texture = nullptr;
static Texture *loadingframe_texture = nullptr;

float loadprogress = 0;
string backgroundcaption = "";
string backgroundmapname = "";
char *backgroundmapinfo = nullptr;
Texture *backgroundmapshot = nullptr;

/// create a resolution suggestion by scaling down the larger side of the 2 screen dimensions.
/// @warning this is a call by reference function!
/// @warning this function uses old style C-casting
static void getbackgroundres(int &w, int &h)
{
    float wk = 1, hk = 1;
    if(w < 1024) wk = 1024.0f/w;
    if(h < 768) hk = 768.0f/h;
    wk = hk = std::max(wk, hk);
    w = int(ceil(w*wk));
    h = int(ceil(h*hk));
}

/// this function is called to render the main menu background once
/// so the loading progress can be rendered over it continuously
/// @see renderbackground
void restorebackground()
{
    if(renderedframe) return;
    renderbackground(backgroundcaption[0] ? backgroundcaption : nullptr, backgroundmapshot,
                     backgroundmapname[0] ? backgroundmapname : nullptr, backgroundmapinfo, true);
}


/// Render a textured quad of the given dimensions.
/// Difference to screenquad is the ability to change the start position (with x and y -> lower left corner of the quad)
void bgquad(float x, float y, float w, float h)
{
    gle::begin(GL_TRIANGLE_STRIP);
    gle::attribf(x,   y);   gle::attribf(0, 0);
    gle::attribf(x+w, y);   gle::attribf(1, 0);
    gle::attribf(x,   y+h); gle::attribf(0, 1);
    gle::attribf(x+w, y+h); gle::attribf(1, 1);
    gle::end();
}

void renderbackground(const char *caption, Texture *mapshot, const char *mapname, const char *mapinfo, bool restore, bool force)
{
    if(!inbetweenframes && !force) return;
    stopsounds(); // stop sounds while loading

    int w = screen_manager.screenw, h = screen_manager.screenh;
    if(forceaspect) w = int(ceil(h*forceaspect));
    getbackgroundres(w, h);
    gettextres(w, h);


    static int lastupdate = -1, lastw = -1, lasth = -1;
    static float backgroundu = 0, backgroundv = 0, detailu = 0, detailv = 0;
    static int numdecals = 0;
    static struct decal { float x, y, size; int side; } decals[12];
    if((renderedframe && !mainmenu && lastupdate != lastmillis) || lastw != w || lasth != h)
    {
        lastupdate = lastmillis;
        lastw = w;
        lasth = h;

        backgroundu = rnd<float>(1);
        backgroundv = rnd<float>(1);
        detailu = rnd<float>(1);
        detailv = rnd<float>(1);
        numdecals = sizeof(decals)/sizeof(decals[0]);
        numdecals = numdecals/3 + rnd<int>((numdecals*2)/3 + 1);
        float maxsize = std::min(w, h)/16.0f;
        loopi(numdecals)
        {
            decal d = { rnd<float>(w), rnd<float>(h), maxsize/2 + rnd<float>(maxsize/2), rnd<int>(2) };
            decals[i] = d;
        }
    }
    else if(lastupdate != lastmillis) lastupdate = lastmillis;

    loopi(restore ? 1 : 3)
    {
        hudmatrix.ortho(0, w, h, 0, -1, 1);
        resethudmatrix();

        hudshader->set();
        gle::colorf(1, 1, 1);

        gle::defvertex(2);
        gle::deftexcoord0();

        if(!background_texture) background_texture = textureload(background, 3, true, false);
        glBindTexture(GL_TEXTURE_2D, background_texture->id);

        bgquad(0, 0, w, h);

        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
        glEnable(GL_BLEND);

        float lh = 0.5f*std::min(w, h), lw = lh*2,
                lx = 0.5f*(w - lw), ly = 0.5f*(h*0.5f - lh);

        if(!logo_texture) logo_texture = textureload(logo, 3, true, false);
        glBindTexture(GL_TEXTURE_2D, logo_texture->id);
        bgquad(lx, ly, lw, lh);
        if(caption)
        {
            int tw = text_width(caption);
            float tsz = 0.04f*std::min(w, h)/FONTH,
                    tx = 0.5f*(w - tw*tsz), ty = h - 0.075f*1.5f*std::min(w, h) - 1.25f*FONTH*tsz;
            pushhudmatrix();
            hudmatrix.translate(tx, ty, 0);
            hudmatrix.scale(tsz, tsz, 1);
            flushhudmatrix();
            draw_text(caption, 0, 0);
            pophudmatrix();
        }
        if(mapshot || mapname)
        {
            int infowidth = 12*FONTH;
            float sz = 0.35f*std::min(w, h), msz = (0.75f*std::min(w, h) - sz)/(infowidth + FONTH), x = 0.5f*(w-sz), y = ly+lh - sz/15;
            if(mapinfo)
            {
                int mw, mh;
                text_bounds(mapinfo, mw, mh, infowidth);
                x -= 0.5f*(mw*msz + FONTH*msz);
            }
            if(mapshot && mapshot!=notexture)
            {
                glBindTexture(GL_TEXTURE_2D, mapshot->id);
                bgquad(x, y, sz, sz);
            }
            else
            {
                int qw, qh;
                text_bounds("?", qw, qh);
                float qsz = sz*0.5f/std::max(qw, qh);
                pushhudmatrix();
                hudmatrix.translate(x + 0.5f*(sz - qw*qsz), y + 0.5f*(sz - qh*qsz), 0);
                hudmatrix.scale(qsz, qsz, 1);
                flushhudmatrix();
                draw_text("?", 0, 0);
                pophudmatrix();
                glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
            }

            if(!mapshotframe_texture)
            {
                std::string filename;
                getmediapath(filename, "mapshot_frame.png", DIR_UI);
                mapshotframe_texture = textureload(filename.c_str(), 3, true, false);
            }
            glBindTexture(GL_TEXTURE_2D, mapshotframe_texture->id);
            bgquad(x, y, sz, sz);

            if(mapname)
            {
                int tw = text_width(mapname);
                float tsz = sz/(8*FONTH),
                        tx = 0.9f*sz - tw*tsz, ty = 0.9f*sz - FONTH*tsz;
                if(tx < 0.1f*sz) { tsz = 0.1f*sz/tw; tx = 0.1f; }
                pushhudmatrix();
                hudmatrix.translate(x+tx, y+ty, 0);
                hudmatrix.scale(tsz, tsz, 1);
                flushhudmatrix();
                draw_text(mapname, 0, 0);
                pophudmatrix();
            }
            if(mapinfo)
            {
                pushhudmatrix();
                hudmatrix.translate(x+sz+FONTH*msz, y, 0);
                hudmatrix.scale(msz, msz, 1);
                flushhudmatrix();
                draw_text(mapinfo, 0, 0, 0xFF, 0xFF, 0xFF, 0xFF, -1, infowidth);
                pophudmatrix();
            }
        }
        glDisable(GL_BLEND);
        if(!restore) screen_manager.swapbuffers(false);
    }

    if(!restore)
    {
        renderedframe = false;
        copystring(backgroundcaption, caption ? caption : "");
        backgroundmapshot = mapshot;
        copystring(backgroundmapname, mapname ? mapname : "");
        if(mapinfo != backgroundmapinfo)
        {
            DELETEA(backgroundmapinfo);
            if(mapinfo) backgroundmapinfo = newstring(mapinfo);
        }
    }
}


/// render progress bar and map screenshot
void renderprogress(float bar, const char *text, GLuint tex, bool background)
{
    if(!inbetweenframes || drawtex) return;

    clientkeepalive();      /// make sure our connection doesn't time out while loading maps etc.

#ifdef __APPLE__
    interceptkey(SDLK_UNKNOWN); /// keep the event queue awake to avoid 'beachball' cursor
#endif

    if(background) restorebackground();

    int w = screen_manager.screenw, h = screen_manager.screenh;
    if(forceaspect) w = int(ceil(h*forceaspect));
    getbackgroundres(w, h);
    gettextres(w, h);

    hudmatrix.ortho(0, w, h, 0, -1, 1);
    resethudmatrix();

    hudshader->set();
    gle::colorf(1, 1, 1);

    gle::defvertex(2);
    gle::deftexcoord0();

    float fh = 0.075f*std::min(w, h), fw = fh*10,
            fx = renderedframe ? w - fw - fh/4 : 0.5f*(w - fw),
            fy = renderedframe ? fh/4 : h - fh*1.5f;

    // Render the loading bar
    if(!loadingframe_texture)
    {
        std::string filename;
        getmediapath(filename, "loading_frame.png", DIR_UI);
        loadingframe_texture = textureload(filename.c_str(), 3, true, false);
    }
    glBindTexture(GL_TEXTURE_2D, loadingframe_texture->id);
    bgquad(fx, fy, fw, fh);

    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    float bw = fw*(511 - 2*17)/511.0f, bh = fh*20/52.0f,
            bx = fx + fw*17/511.0f, by = fy + fh*16/52.0f,
            bv1 = 0/32.0f, bv2 = 20/32.0f,
            su1 = 0/32.0f, su2 = 7/32.0f, sw = fw*7/511.0f,
            eu1 = 23/32.0f, eu2 = 30/32.0f, ew = fw*7/511.0f,
            mw = bw - sw - ew,
            ex = bx+sw + std::max(mw*bar, fw*7/511.0f);
    if(bar > 0)
    {
        if(!loadingbar_texture)
        {
            std::string filename;
            getmediapath(filename, "loading_bar.png", DIR_UI);
            loadingbar_texture = textureload(filename.c_str(), 3, true, false);
        }
        glBindTexture(GL_TEXTURE_2D, loadingbar_texture->id);
        gle::begin(GL_QUADS);
        gle::attribf(bx,    by);    gle::attribf(su1, bv1);
        gle::attribf(bx+sw, by);    gle::attribf(su2, bv1);
        gle::attribf(bx+sw, by+bh); gle::attribf(su2, bv2);
        gle::attribf(bx,    by+bh); gle::attribf(su1, bv2);

        gle::attribf(bx+sw, by);    gle::attribf(su2, bv1);
        gle::attribf(ex,    by);    gle::attribf(eu1, bv1);
        gle::attribf(ex,    by+bh); gle::attribf(eu1, bv2);
        gle::attribf(bx+sw, by+bh); gle::attribf(su2, bv2);

        gle::attribf(ex,    by);    gle::attribf(eu1, bv1);
        gle::attribf(ex+ew, by);    gle::attribf(eu2, bv1);
        gle::attribf(ex+ew, by+bh); gle::attribf(eu2, bv2);
        gle::attribf(ex,    by+bh); gle::attribf(eu1, bv2);
        gle::end();
    }

    // render the info stuff

    // map/mode description
    if(text)
    {
        int tw = text_width(text);
        float tsz = bh*0.8f/FONTH;
        if(tw*tsz > mw) tsz = mw/tw;
        pushhudmatrix();
        hudmatrix.translate(bx+sw, by + (bh - FONTH*tsz)/2, 0);
        hudmatrix.scale(tsz, tsz, 1);
        flushhudmatrix();
        draw_text(text, 0, 0);
        pophudmatrix();
    }

    glDisable(GL_BLEND);

    if(tex) //render the map shot/lightmap
    {
        glBindTexture(GL_TEXTURE_2D, tex);
        float sz = 0.35f*std::min(w, h), x = 0.5f*(w-sz), y = 0.5f*std::min(w, h) - sz/15;
        bgquad(x, y, sz, sz);

        glEnable(GL_BLEND);
        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

        if(!mapshotframe_texture)
        {
            std::string filename;
            getmediapath(filename, "mapshot_frame.png", DIR_UI);
            mapshotframe_texture = textureload(filename.c_str(), 3, true, false);
        }
        glBindTexture(GL_TEXTURE_2D, mapshotframe_texture->id);
        bgquad(x, y, sz, sz);

        glDisable(GL_BLEND);
    }

    screen_manager.swapbuffers(false);
}
