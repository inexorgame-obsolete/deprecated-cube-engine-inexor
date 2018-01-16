/// game initialisation & main loop
///
#include <boost/algorithm/clamp.hpp>                  // for clamp
#include <locale.h>                                   // for setlocale, LC_ALL
#include <math.h>                                     // for ceil
#include <stdio.h>                                    // for remove
#include <stdlib.h>                                   // for exit, EXIT_FAILURE, atexit
#include <string.h>                                   // for strstr
#include <algorithm>                                  // for min, max
#include <memory>                                     // for __shared_ptr
#include <string>                                     // for string, basic_s...
#include <vector>                                     // for vector

#include "SDL.h"                                      // for SDL_Quit, SDL_Init
#include "SDL_cpuinfo.h"                              // for SDL_GetCPUCount
#include "SDL_error.h"                                // for SDL_GetError
#include "SDL_hints.h"                                // for SDL_SetHint
#include "SDL_mouse.h"                                // for SDL_ShowCursor
#include "SDL_opengl.h"                               // for glBindTexture
#include "SDL_stdinc.h"                               // for ::SDL_FALSE
#include "SDL_video.h"                                // for SDL_SetWindowBr...
#include "enet/enet.h"                                // for enet_initialize
#include "inexor/crashreporter/CrashReporter.hpp"     // for CrashReporter
#include "inexor/engine/decal.hpp"                    // for initdecals
#include "inexor/engine/engine.hpp"                   // for gl_init, writecfg
#include "inexor/engine/glemu.hpp"                    // for attribf, begin
#include "inexor/engine/lightmap.hpp"                 // for initlights
#include "inexor/engine/movie.hpp"                    // for cleanup, stop
#include "inexor/engine/octree.hpp"                     // for worldroot
#include "inexor/engine/octaedit.hpp"                 // for tryedit
#include "inexor/engine/rendertext.hpp"               // for FONTH
#include "inexor/engine/shader.hpp"                   // for Shader, hudshader
#include "inexor/engine/frame.hpp"
#include "inexor/io/Logging.hpp"                      // for Log, log_manager
#include "inexor/io/filesystem/mediadirs.hpp"         // for getmediapath
#include "inexor/io/input/InputRouter.hpp"            // for InputRouter
#include "inexor/io/legacy/stream.hpp"                // for stream, addpack...
#include "inexor/network/SharedFunc.hpp"              // for SharedFunc
#include "inexor/network/SharedVar.hpp"               // for SharedVar, min
#include "inexor/shared/command.hpp"                  // for execfile, VARF
#include "inexor/shared/cube_formatting.hpp"          // for defvformatstring
#include "inexor/shared/cube_loops.hpp"               // for loopi, i
#include "inexor/shared/cube_tools.hpp"               // for copystring, new...
#include "inexor/shared/cube_types.hpp"               // for string
#include "inexor/shared/ents.hpp"                     // for dynent
#include "inexor/shared/geom.hpp"                     // for matrix4
#include "inexor/shared/iengine.hpp"                  // for draw_text, flus...
#include "inexor/shared/igame.hpp"                    // for savedservers
#include "inexor/shared/tools.hpp"                    // for rndscale, min, rnd
#include "inexor/sound/mumble.hpp"                    // for initmumble
#include "inexor/sound/sound.hpp"                     // for clear_sound
#include "inexor/texture/texture.hpp"                 // for textureload
#include "inexor/ui/legacy/menus.hpp"                 // for initwarning
#include "inexor/ui/screen/ScreenManager.hpp"         // for ScreenManager
#include "inexor/util/StringFormatter.hpp"            // for StringFormatter
#include "inexor/util/Subsystem.hpp"                  // for Metasystem, SUB...
#include "inexor/util/legacy_time.hpp"                // for lastmillis, upd...

using namespace inexor::sound;
using namespace inexor::io;
using namespace inexor::rendering::screen;

extern void writeinitcfg();

/// local player
dynent *player = nullptr;

int initing = NOT_INITING;

inexor::util::Metasystem metapp;

/// cleans up game memory and SDL at exit
void cleanup()
{
    extern void clear_command();
    extern void clear_console();
    extern void clear_mdls();

    recorder::stop();

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
    writecfg();
    cleanup();
    metapp.stop("cef");
    metapp.stop("rpc");
    exit(EXIT_SUCCESS);
}
COMMAND(quit, "");

SharedFunc(quit);

void cleanup_application()
{
    screen_manager.cleanupSDL();
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
            Log.std->error("Could not set gamma: {}", SDL_GetError());
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



VAR(numcpus, 1, 1, 16);

/// find command line argument
static bool findarg(int argc, char **argv, const char *str)
{
    for(int i = 1; i<argc; i++) if(strstr(argv[i], str)==argv[i]) return true;
    return false;
}

ICOMMANDERR(subsystem_start, "s", (char *s), std::string ccs{s}; metapp.start(ccs));
ICOMMANDERR(subsystem_stop, "s", (char *s), std::string ccs{s}; metapp.stop(ccs));

//inexor::util::Logging logging;
//
//ICOMMANDERR(loglevel, "ss", (char *logger_name, char *log_level),
//    std::string logger_name_s{logger_name};
//    std::string log_level_s{log_level};
//    logging.setLogLevel(logger_name_s, log_level_s)
//);
//
//ICOMMANDERR(logformat, "ss", (char *logger_name, char *pattern),
//    std::string logger_name_s{logger_name};
//    std::string pattern_s{pattern};
//    logging.setLogFormat(logger_name_s, pattern_s)
//);

// temporal workaround for Sharedlists
SharedVar<char *> package_dir((char*)"media/essential");
SharedVar<char *> package_dir2((char*)"media/additional");

int main(int argc, char **argv)
{
    char *exe_name = argv[0];
    Log.logfile = exe_name;

    // We only need to initialize it, not use it.
    UNUSED inexor::crashreporter::CrashReporter SingletonStackwalker; // catches all msgs from the OS, that it wants to terminate us.

    // Ensure the correct locale
    setlocale(LC_ALL, "en_US.utf8");

    char *initscript = nullptr;

    // Initialize the metasystem
    // Remote Procedure Call: communication with the scripting engine
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

    Log.start_stop->info("init: SDL");

    int par = 0;
    #ifdef _DEBUG
        par = SDL_INIT_NOPARACHUTE;
    #endif
    if(SDL_Init(SDL_INIT_TIMER|SDL_INIT_VIDEO|SDL_INIT_AUDIO|par)<0)
        fatal("Unable to initialize SDL: %s", SDL_GetError());

    // Ensure we run SDL_QUIT at exit
    atexit(SDL_Quit);

    const char *dir = addpackagedir(package_dir);
    if(dir) Log.start_stop->info("Adding package directory: {}", dir);
    dir = addpackagedir(package_dir2);
    if(dir) Log.start_stop->info("Adding package directory: {}", dir);

    Log.start_stop->info("init: ENet");
    if(enet_initialize()<0) fatal("Unable to initialize network module");
    atexit(enet_deinitialize);
    enet_time_set(0);

    Log.start_stop->info("init: game");

    game::initclient();

    Log.start_stop->info("init: video");

    SDL_SetHint(SDL_HINT_GRAB_KEYBOARD, "0");
    #if !defined(WIN32) && !defined(__APPLE__)
       SDL_SetHint(SDL_HINT_VIDEO_MINIMIZE_ON_FOCUS_LOSS, "0");
    #endif

    int useddepthbits = 0, usedfsaa = 0;
    screen_manager.setupscreen(useddepthbits, usedfsaa);
    SDL_ShowCursor(SDL_FALSE);

    Log.start_stop->info("init: gl");
    gl_checkextensions();
    gl_init(useddepthbits, usedfsaa);
    notexture = textureload("texture/inexor/notexture.png");
    if(!notexture) fatal("could not find core textures");

    Log.start_stop->info("init: console");
    if(!execfile("config/stdlib.cfg", false)) fatal("cannot find config files");
    if(!execfile("config/font.cfg", false)) fatal("cannot find font definitions");
    if(!setfont("default")) fatal("no default font specified");

    inbetweenframes = true;
    renderbackground("initializing...");

    Log.start_stop->info("init: effects");
    loadshaders();
    particleinit();
    initdecals();

    Log.start_stop->info("init: world");
    camera1 = player = game::iterdynents(0);
    emptymap(0, true, nullptr, false);

    Log.start_stop->info("init: sound");
    initsound();

    Log.start_stop->info("init: cfg");
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

    loadhistory();
    if(initscript) execute(initscript);

    Log.start_stop->info("init: mainloop");

    initmumble();
    resetfpshistory();

    input_router.set_grab_input(true);
    input_router.inputgrab();
    input_router.ignoremousemotion();

    // main game loop
    for(;;)
    {
        static int frames = 0;

        int fps_limit = get_current_max_fps();
        updatetime(game::ispaused(), game::gamespeed, fps_limit);

        metapp.tick();

        input_router.checkinput();
        menuprocess();
        tryedit();

        if(lastmillis) game::updateworld();

        checksleep(lastmillis);

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
