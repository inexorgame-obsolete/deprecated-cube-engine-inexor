#pragma once

#include <vector>
#include <SDL.h>

#include "inexor/network/SharedTree.hpp"

namespace inexor {
namespace io {

enum
{
    INPUT_LAYER_GAME = 0,
    INPUT_LAYER_HUD,
    INPUT_LAYER_APP,
    INPUT_LAYER_CHAT
};

enum
{
    INPUT_LAYER_GAME_PLAY = 0,
    INPUT_LAYER_GAME_EDIT,
    INPUT_LAYER_GAME_SPEC
};

/// Forwards input events to the subsystem they are needed.
class InputRouter
{
    public:
        InputRouter();
        virtual ~InputRouter();

        /// Check if key was pressed repeatedly using bit masking technique
        void keyrepeat(bool on, int mask);

        /// Do grab the input depending on the current grab mode
        void inputgrab();

        /// Sets input grab mode for mouse and keyboard
        void set_grab_input(bool grab_input);

        /// "abort" key to interrupt updating the masterlist,
        /// connecting to a server or computing lightmaps
        bool interceptkey(int sym);

        void ignoremousemotion();

        /// Periodically checking for new input
        void checkinput();

        // BIND MANAGER
        // check_bind
        // bool filter_input_layer()

        bool relativemouse;

    private:

        /// add a new event to event vector
        void pushevent(const SDL_Event &e);

        /// filter mouse motion events depending on operating system
        bool filterevent(const SDL_Event &event);

        /// poll and filter all events in the SDL (input) event queue
        /// @see SDL_PollEvent
        /// @see filterevent
        bool pollevent(SDL_Event &event);

        /// move mouse to screen center
        /// @see SDL_WarpMouseInWindow
        void resetmousemotion();

        /// handle mouse motion coordinates
        /// @returns deltax and deltay (the difference of the mouse coords)
        void checkmousemotion(int &dx, int &dy);

        /// global vector for input events
        std::vector<SDL_Event> events;

        /// controlling input devices using Simple DirectMedia Layer
        bool shouldgrab;
        bool grabinput;
        bool canrelativemouse;

        /// key repetition is stored in bit masks
        int keyrepeatmask;

        /// text input state is also stored in bit masks
        int textinputmask;

};

/// InputRouter singleton
extern InputRouter input_router;

// Provide global exports
extern SharedVar<int> userelativemouse;

}
}
