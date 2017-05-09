/// game initialisation & main loop
///
#include "inexor/engine/engine.hpp"
#include "inexor/engine/sound.hpp"
#include "inexor/filesystem/mediadirs.hpp"
#include "inexor/ui.hpp"
#include "inexor/ui/input/InputRouter.hpp"
#include "inexor/ui/screen/ScreenManager.hpp"
#include "inexor/util/Subsystem.hpp"
#include "inexor/crashreporter/CrashReporter.hpp"
#include "inexor/util/Logging.hpp"
#include "inexor/network/SharedTree.hpp"
#include "inexor/network/SharedList.hpp"
#include "inexor/util/legacy_time.hpp"

//template<typename T>
//class SharedList
//{
//    size_t length = 0;
//  public:
//    void push_back(SharedVar<T> &x)
//    {
//        SharedVar.connect([]{ int id = length;});
//        length++;
//    }
//};
namespace inexor { namespace rendering {

player player1;

} } // ns inexor::rendering

inexor::rendering::player player2;

using namespace inexor;

rendering::player player3;
SharedList<rendering::player> testbliat;

void testfunction(char *init, string num2)
{

}

void testfunction(const char *init = "maybe im a string")
{

}

void testfunction(int init,
                  int initf);

void testfunction(int init, float initf)
{

}
SharedFunc(testfunction)

void testfunction(int init,
                  int initf) { }

using namespace inexor::sound;
using namespace inexor::io;
using namespace inexor::rendering::screen;

extern void writeinitcfg();

/// local player
dynent *player = NULL;

int initing = NOT_INITING;

inexor::util::Metasystem metapp;

/// cleans up game memory and SDL at exit
void cleanup()
{
    extern void clear_command();
    extern void clear_console();
    extern void clear_mdls();

    recorder::stop();
    cleanupserver();

    screen_manager.cleanupSDL();

    freeocta(worldroot);
    clear_command();
    clear_console();
    clear_mdls();
    inexor::sound::clear_sound();
    // closelogfile();

    SDL_Quit();
}

/// normal game quit
/// @see fatal
/// @see cleanup
void quit()
{
    writeinitcfg();
    writehistory();
    abortconnect();
    disconnect();
    localdisconnect();
    writecfg();
    cleanup();
    metapp.stop("cef");
    metapp.stop("rpc");
    exit(EXIT_SUCCESS);
}
COMMAND(quit, "");

SharedFunc(quit);

/// Fatal crash: log/display crash message and clean up SDL.
void fatal(const char *s, ...)
{
    screen_manager.cleanupSDL();
    static int errors = 0;
    errors++;
    if(errors <= 2) // print up to one extra recursive error
    {
        defvformatstring(msg,s,s);
        // Temporarly disabled crash handler output (easylogging)
        spdlog::get("global")->critical(msg);

        #ifdef WIN32
            if(errors <= 1) MessageBox(NULL, msg, "Inexor fatal error", MB_OK|MB_SYSTEMMODAL);
        #endif
    }
    SDL_Quit();
    exit(EXIT_FAILURE);
}

/// Fatal crash: log/display crash message and clean up SDL.
void fatal(std::vector<std::string> &output)
{
    screen_manager.cleanupSDL();
    std::string completeoutput; 
    for(auto message : output) {
        // Temporarly disabled crash handler output (easylogging)
        spdlog::get("global")->critical(message);
        completeoutput = inexor::util::fmt << completeoutput << message.c_str();
    }
#ifdef WIN32
    MessageBox(NULL, completeoutput.c_str(), "Inexor fatal error", MB_OK | MB_SYSTEMMODAL);
#endif
    SDL_Quit();
    exit(EXIT_FAILURE);
}

/// print initialisation (bug hints) warning in game console
/// @see addchange
bool initwarning(const char *desc, int level, int type)
{
    if(initing < level) 
    {
        addchange(desc, type);
        return true;
    }
    return false;
}


/// ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
/// screen setup and window settings


/// function forward to change screen resolution
namespace inexor {
namespace rendering {
namespace screen {

    // TODO: CEF userinterface
    ICOMMAND(screenres, "ii", (int *w, int *h), screen_manager.screenres(*w, *h));

    /// change screen width and height
    VARF(scr_w, SCR_MINW, -1, SCR_MAXW, screen_manager.screenres(scr_w, -1));
    VARF(scr_h, SCR_MINH, -1, SCR_MAXH, screen_manager.screenres(-1, scr_h));

    /// various buffer precisions and anti aliasing
    /// @see initwarning
    VAR(colorbits, 0, 0, 32);
    VARF(depthbits, 0, 0, 32, initwarning("depth-buffer precision"));
    VARF(stencilbits, 0, 0, 32, initwarning("stencil-buffer precision"));

    /// VSYNC settings
    VARFP(vsync, 0, 0, 1, screen_manager.restorevsync());
    VARFP(vsynctear, 0, 0, 1, { if(vsync) screen_manager.restorevsync(); });

    VARF(fsaa, -1, -1, 16, initwarning("anti-aliasing"));

    /// @warning do not go full screen in debug mode (doesn't work with MSVC)
#ifdef _DEBUG
    VARF(fullscreen, 0, 0, 1, screen_manager.setfullscreen(fullscreen!=0));
#else
    VARF(fullscreen, 0, 1, 1, screen_manager.setfullscreen(fullscreen!=0));
#endif

    /// screen gamma as float value
    // static int curgamma = 100;
    VARFP(gamma, 30, 100, 300,
    {
        if(gamma == screen_manager.curgamma) return;
        screen_manager.curgamma = gamma;
        if(SDL_SetWindowBrightness(screen_manager.sdl_window, gamma/100.0f)==-1)
            spdlog::get("global")->error("Could not set gamma: {}", SDL_GetError());
    });
}
}
}

/// write most important settings to init.cfg using an UTF-8 stream
/// @see openutf8file
void writeinitcfg()
{
    stream *f = openutf8file("init.cfg", "w");
    if(!f) return;
    f->printf("// automatically written on exit, DO NOT MODIFY\n// modify settings in game\n");

    f->printf("fullscreen %d\n", *fullscreen);
    f->printf("screenres %d %d\n", *scr_w, *scr_h);
    f->printf("colorbits %d\n", *colorbits);
    f->printf("depthbits %d\n", *depthbits);
    f->printf("stencilbits %d\n", *stencilbits);
    f->printf("fsaa %d\n", *fsaa);
    f->printf("vsync %d\n", *vsync);
    f->printf("vsynctear %d\n", *vsynctear);
    extern SharedVar<int> shaderprecision;
    f->printf("shaderprecision %d\n", *shaderprecision);
    f->printf("soundchans %d\n", *inexor::sound::soundchans);
    f->printf("soundfreq %d\n", *inexor::sound::soundfreq);
    f->printf("soundbufferlen %d\n", *inexor::sound::soundbufferlen);
    delete f;
}


/// ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
/// main menu background and loading screen renderer

static Texture *logo_texture = NULL;
static Texture *background_texture = NULL;
SVARFP(background, "interface/background.png", background_texture = NULL;);
SVARFP(logo, "interface/logo.png", logo_texture = NULL;);

static Texture *mapshotframe_texture = NULL;
static Texture *loadingbar_texture = NULL;
static Texture *loadingframe_texture = NULL;

float loadprogress = 0;
string backgroundcaption = "";
string backgroundmapname = "";
char *backgroundmapinfo = NULL;
Texture *backgroundmapshot = NULL;

/// create a resolution suggestion by scaling down the larger side of the 2 screen dimensions.
/// @warning this is a call by reference function!
/// @warning this function uses old style C-casting
static void getbackgroundres(int &w, int &h)
{
    float wk = 1, hk = 1;
    if(w < 1024) wk = 1024.0f/w;
    if(h < 768) hk = 768.0f/h;
    wk = hk = max(wk, hk);
    w = int(ceil(w*wk));
    h = int(ceil(h*hk));
}

/// this function is called to render the main menu background once
/// so the loading progress can be rendered over it continuously
/// @see renderbackground
void restorebackground()
{
    if(renderedframe) return;
    renderbackground(backgroundcaption[0] ? backgroundcaption : NULL, backgroundmapshot, backgroundmapname[0] ? backgroundmapname : NULL, backgroundmapinfo, true);
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

/// render map loading progress screen (and background) including map name and game mode info
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

        backgroundu = rndscale(1);
        backgroundv = rndscale(1);
        detailu = rndscale(1);
        detailv = rndscale(1);
        numdecals = sizeof(decals)/sizeof(decals[0]);
        numdecals = numdecals/3 + rnd((numdecals*2)/3 + 1);
        float maxsize = min(w, h)/16.0f;
        loopi(numdecals)
        {
            decal d = { rndscale(w), rndscale(h), maxsize/2 + rndscale(maxsize/2), rnd(2) };
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

        float lh = 0.5f*min(w, h), lw = lh*2,
              lx = 0.5f*(w - lw), ly = 0.5f*(h*0.5f - lh);

        if(!logo_texture) logo_texture = textureload(logo, 3, true, false);
        glBindTexture(GL_TEXTURE_2D, logo_texture->id);
        bgquad(lx, ly, lw, lh);
        if(caption)
        {
            int tw = text_width(caption);
            float tsz = 0.04f*min(w, h)/FONTH,
                  tx = 0.5f*(w - tw*tsz), ty = h - 0.075f*1.5f*min(w, h) - 1.25f*FONTH*tsz;
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
            float sz = 0.35f*min(w, h), msz = (0.75f*min(w, h) - sz)/(infowidth + FONTH), x = 0.5f*(w-sz), y = ly+lh - sz/15;
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
                float qsz = sz*0.5f/max(qw, qh);
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
                inexor::filesystem::getmediapath(filename, "mapshot_frame.png", DIR_UI);
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

    float fh = 0.075f*min(w, h), fw = fh*10,
          fx = renderedframe ? w - fw - fh/4 : 0.5f*(w - fw), 
          fy = renderedframe ? fh/4 : h - fh*1.5f;

    // Render the loading bar
    if(!loadingframe_texture)
    {
        std::string filename;
        inexor::filesystem::getmediapath(filename, "loading_frame.png", DIR_UI);
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
          ex = bx+sw + max(mw*bar, fw*7/511.0f);
    if(bar > 0)
    {
        if(!loadingbar_texture)
        {
            std::string filename;
            inexor::filesystem::getmediapath(filename, "loading_bar.png", DIR_UI);
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
        float sz = 0.35f*min(w, h), x = 0.5f*(w-sz), y = 0.5f*min(w, h) - sz/15;
        bgquad(x, y, sz, sz);

        glEnable(GL_BLEND);
        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

        if(!mapshotframe_texture)
        {
            std::string filename;
            inexor::filesystem::getmediapath(filename, "mapshot_frame.png", DIR_UI);
            mapshotframe_texture = textureload(filename.c_str(), 3, true, false);
        }
        glBindTexture(GL_TEXTURE_2D, mapshotframe_texture->id);
        bgquad(x, y, sz, sz);

        glDisable(GL_BLEND);
    }

    screen_manager.swapbuffers(false);
}



namespace inexor {
namespace io {
    /// try to initialise mouse with relative coordinates instead of absolute coordinates
    VARNP(input_router.relativemouse, userelativemouse, 0, 1, 1);
}
}

/// reset OpenGL manually (/resetgl command)
/// this function is not called in the entire code
void resetgl()
{
    clearchanges(CHANGE_GFX);
    renderbackground("resetting OpenGL");

    extern void cleanupva();
    extern void cleanupparticles();
    extern void cleanupdecals();
    extern void cleanupblobs();
    extern void cleanupsky();
    extern void cleanupmodels();
    extern void cleanupprefabs();
    extern void cleanuptextures();
    extern void cleanuplightmaps();
    extern void cleanupblendmap();
    extern void cleanshadowmap();
    extern void cleanreflections();
    extern void cleanupglare();
    extern void cleanupdepthfx();
    extern void cleanupshaders();
    extern void cleanupgl();
    extern void reloadfonts();
    extern void reloadtextures();
    extern void reloadshaders();

    recorder::cleanup();
    cleanupva();
    cleanupparticles();
    cleanupblobs();
    cleanupsky();
    cleanupmodels();
    cleanupprefabs();
    cleanuptextures();
    cleanuplightmaps();
    cleanupblendmap();
    cleanshadowmap();
    cleanreflections();
    cleanupglare();
    cleanupdepthfx();
    cleanupshaders();
    cleanupgl();
    
    int useddepthbits = 0, usedfsaa = 0;
    screen_manager.setupscreen(useddepthbits, usedfsaa);

    input_router.inputgrab();

    gl_init(useddepthbits, usedfsaa);
    inbetweenframes = false;
    if(!reloadtexture(*notexture) || //todo
       !reloadtexture("interface/logo.png") ||
       !reloadtexture("interface/background.png") ||
       !reloadtexture("interface/mapshot_frame.png") ||
       !reloadtexture("interface/loading_frame.png") ||
       !reloadtexture("interface/loading_bar.png"))
        fatal("failed to reload core texture");
    reloadfonts();
    inbetweenframes = true;
    renderbackground("initializing...");
    screen_manager.restoregamma();
    reloadshaders();
    reloadtextures();
    initlights();
    allchanged(true);
}
COMMAND(resetgl, "");

/// frames per seconds and timing

/// store the last MAXFPSHISTORY fps rates 
#define MAXFPSHISTORY 60
int fpspos = 0, fpshistory[MAXFPSHISTORY];
bool inbetweenframes = false, renderedframe = true;

VAR(menufps, 0, 60, 1000);
VARP(maxfps, 0, 200, 1000);

/// clear fps history array
void resetfpshistory()
{
    loopi(MAXFPSHISTORY) fpshistory[i] = 1;
    fpspos = 0;
}

/// add current frames per seconds score to fps history array
void updatefpshistory(int millis)
{
    fpshistory[fpspos++] = max(1, min(1000, millis));
    if(fpspos>=MAXFPSHISTORY) fpspos = 0;
}

/// get average fps, best fps and worst fps (see command fpsrange)
void getfps(int &fps, int &bestdiff, int &worstdiff)
{
    int total = fpshistory[MAXFPSHISTORY-1], best = total, worst = total;
    loopi(MAXFPSHISTORY-1)
    {
        int millis = fpshistory[i];
        total += millis;
        if(millis < best) best = millis;
        if(millis > worst) worst = millis;
    }

    fps = (1000*MAXFPSHISTORY)/total;
    bestdiff = 1000/best-fps;
    worstdiff = fps-1000/worst;
}


/// cubescript: get fps as float
/// @see floatret
void getfps_(int *raw)
{
    if(*raw) floatret(1000.0f/fpshistory[(fpspos+MAXFPSHISTORY-1)%MAXFPSHISTORY]);
    else
    {
        int fps, bestdiff, worstdiff;
        getfps(fps, bestdiff, worstdiff);
        intret(fps);
    }
}
COMMANDN(getfps, getfps_, "i");

VAR(numcpus, 1, 1, 16);

/// find command line argument
static bool findarg(int argc, char **argv, const char *str)
{
    for(int i = 1; i<argc; i++) if(strstr(argv[i], str)==argv[i]) return true;
    return false;
}

ICOMMANDERR(subsystem_start, "s", (char *s), std::string ccs{s}; metapp.start(ccs));
ICOMMANDERR(subsystem_stop, "s", (char *s), std::string ccs{s}; metapp.stop(ccs));

inexor::util::Logging logging;

ICOMMANDERR(loglevel, "ss", (char *logger_name, char *log_level),
    std::string logger_name_s{logger_name};
    std::string log_level_s{log_level};
    logging.setLogLevel(logger_name_s, log_level_s)
);

ICOMMANDERR(logformat, "ss", (char *logger_name, char *pattern),
    std::string logger_name_s{logger_name};
    std::string pattern_s{pattern};
    logging.setLogFormat(logger_name_s, pattern_s)
);

SharedVar<char *> package_dir((char*)"media/core");

int main(int argc, char **argv)
{
    logging.initDefaultLoggers();

    // We only need to initialize it, not use it.
    UNUSED inexor::crashreporter::CrashReporter SingletonStackwalker; // catches all msgs from the OS, that it wants to terminate us. 

    // Ensure the correct locale
    setlocale(LC_ALL, "en_US.utf8");
    int dedicated = 0;
    char *load = NULL, *initscript = NULL;

    // Initialize the metasystem
    // remote process control: communication with the scripting engine
    SUBSYSTEM_REQUIRE(rpc);
    // (embedded chromium): ingame html5+js browser for the ui. must come after rpc.. todo new system.
    SUBSYSTEM_REQUIRE(cef);

    // Initialize the submodules
    metapp.start("rpc");
    metapp.initialize("rpc", argc, argv);
    metapp.start("cef");
    metapp.initialize("cef", argc, argv);

    // After submodule initialization force the correct locale
    setlocale(LC_ALL, "en_US.utf8");

    initing = INIT_RESET;
    execfile("init.cfg", false);

    initing = NOT_INITING;

    numcpus = clamp(SDL_GetCPUCount(), 1, 16);

    if(dedicated <= 1)
    {
        spdlog::get("global")->debug("init: SDL");

        int par = 0;
        #ifdef _DEBUG
           par = SDL_INIT_NOPARACHUTE;
        #endif
        if(SDL_Init(SDL_INIT_TIMER|SDL_INIT_VIDEO|SDL_INIT_AUDIO|par)<0) fatal("Unable to initialize SDL: %s", SDL_GetError());
    }

    const char *dir = addpackagedir(package_dir);
    if(dir) spdlog::get("global")->debug("Adding package directory: {}", dir);

    spdlog::get("global")->debug("init: ENet");
    if(enet_initialize()<0) fatal("Unable to initialize network module");
    atexit(enet_deinitialize);
    enet_time_set(0);

    spdlog::get("global")->debug("init: game");

    initserver(dedicated>0, dedicated>1);  /// never returns if dedicated
    ASSERT(dedicated <= 1);
    game::initclient();

    spdlog::get("global")->debug("init: video");

    SDL_SetHint(SDL_HINT_GRAB_KEYBOARD, "0");
    #if !defined(WIN32) && !defined(__APPLE__)
       SDL_SetHint(SDL_HINT_VIDEO_MINIMIZE_ON_FOCUS_LOSS, "0");
    #endif

    int useddepthbits = 0, usedfsaa = 0;
    screen_manager.setupscreen(useddepthbits, usedfsaa);
    SDL_ShowCursor(SDL_FALSE);

    spdlog::get("global")->debug("init: gl");
    gl_checkextensions();
    gl_init(useddepthbits, usedfsaa);
    notexture = textureload("texture/inexor/notexture.png");
    if(!notexture) fatal("could not find core textures");

    spdlog::get("global")->debug("init: console");
    if(!execfile("config/stdlib.cfg", false)) fatal("cannot find config files");
    if(!execfile("config/font.cfg", false)) fatal("cannot find font definitions");
    if(!setfont("default")) fatal("no default font specified");

    inbetweenframes = true;
    renderbackground("initializing...");

    spdlog::get("global")->debug("init: effects");
    loadshaders();
    particleinit();
    initdecals();

    spdlog::get("global")->debug("init: world");
    camera1 = player = game::iterdynents(0);
    emptymap(0, true, NULL, false);

    spdlog::get("global")->debug("init: sound");
    initsound();

    spdlog::get("global")->debug("init: cfg");
    execfile("config/keymap.cfg");
    execfile("config/stdedit.cfg");
    execfile("config/menus.cfg");
    execfile("config/sounds.cfg");
    execfile("config/heightmap.cfg");
    execfile("config/blendbrush.cfg");
    if(game::savedservers()) execfile(game::savedservers(), false);
    
    identflags |= IDF_PERSIST;
    
    initing = INIT_LOAD;
    if(!execfile(game::savedconfig(), false))
    {
        execfile(game::defaultconfig());
        writecfg(game::restoreconfig());
    }
    execfile(game::autoexec(), false);
    initing = NOT_INITING;

    identflags &= ~IDF_PERSIST;

    execfile("config/game_fps.cfg");

    identflags |= IDF_PERSIST;

    if(execfile("once.cfg", false)) remove(findfile("once.cfg", "rb"));

    if(load)
    {
        spdlog::get("global")->debug("init: localconnect");
        //localconnect();
        game::changemap(load);
    }

	loadhistory();
    if(initscript) execute(initscript);

    spdlog::get("global")->debug("init: mainloop");

    initmumble();
    resetfpshistory();

    input_router.set_grab_input(true);
    input_router.inputgrab();
    input_router.ignoremousemotion();

    // main game loop
    for(;;)
    {
        static int frames = 0;

        int fps_limit = (mainmenu || screen_manager.minimized) && menufps ? (maxfps ? min(maxfps, menufps) : menufps) : maxfps;
        updatetime(game::ispaused(), gamespeed, fps_limit);

        metapp.tick();

        input_router.checkinput();
        menuprocess();
        tryedit();

        if(lastmillis) game::updateworld();

        checksleep(lastmillis);

        serverslice(false, 0);

        if(frames) updatefpshistory(elapsedtime);
        frames++;

        // miscellaneous general game effects
        recomputecamera();
        updateparticles();
        updatesounds();

        if(screen_manager.minimized) continue;

        inbetweenframes = false;

        if(mainmenu) gl_drawmainmenu();
        else gl_drawframe();

        screen_manager.swapbuffers();

        renderedframe = inbetweenframes = true;
    }

    ASSERT(0);
    return EXIT_FAILURE;
}
