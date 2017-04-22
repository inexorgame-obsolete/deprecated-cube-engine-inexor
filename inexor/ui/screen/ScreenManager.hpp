#pragma once

#include <SDL.h>

#include "inexor/network/SharedTree.hpp"

/// Hard coded defaults for the SDL window
#define SCR_MINW 320
#define SCR_MINH 200
#define SCR_MAXW 10000
#define SCR_MAXH 10000
#define SCR_DEFAULTW 1024
#define SCR_DEFAULTH 768

namespace inexor {
namespace rendering {
namespace screen {

/// The screen manager manages the SDL window
class ScreenManager
{
    public:
        /// The default constructor
        ScreenManager();

        /// The default destructor
        virtual ~ScreenManager();

        /// Changes the screen resolution
        void screenres(int w, int h);

        /// Switch to fullscreen or windowed mode
        void setfullscreen(bool enable);

        /// Setting up screen using various attempts with different options
        /// @see SDL_GL_SetAttribute
        void setupscreen(int &useddepthbits, int &usedfsaa);

        /// Set screen gamma using float value
        /// @see curgamma
        void restoregamma();

        /// Set screen to normal gamma
        void cleargamma();

        /// "use this function to set the swap interval for the current OpenGL context" (VSYNC)
        void restorevsync();

        /// Clean up SDL
        void cleanupSDL();

        /// swapping buffers allows to render to a new buffer
        /// while the other is being presented to the screen
        /// @see SDL_GL_SwapWindow
        void swapbuffers(bool overlay = true);

        void set_minimized(bool minimized);
        bool is_minimized();

        /// screen resolution management
        int screenw;
        int screenh;
        int desktopw;
        int desktoph;

        /// If true, the window is minimized.
        bool minimized;

        bool initwindowpos;

        int curgamma;

        /// Simple DirectMedia Window and Layer
        SDL_Window *sdl_window;
        SDL_GLContext glcontext = NULL;

    private:

};

// Provide global exports

extern ScreenManager screen_manager;
// TODO: for now: not part of the ScreenManager
extern SharedVar<int> scr_w, scr_h;
extern SharedVar<int> fullscreen, vsync, vsynctear;
extern SharedVar<int> colorbits, depthbits, stencilbits;
extern SharedVar<int> fsaa;

}
}
}
