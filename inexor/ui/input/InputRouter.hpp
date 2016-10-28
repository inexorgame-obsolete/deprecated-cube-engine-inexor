#pragma once

#include <vector>
#include <SDL.h>

#include "inexor/rpc/SharedTree.hpp"

#define INPUT_LAYER_GAME 0
#define INPUT_LAYER_HUD  1
#define INPUT_LAYER_APP  2
#define INPUT_LAYER_CHAT 3

#define INPUT_LAYER_GAME_PLAY 0
#define INPUT_LAYER_GAME_EDIT 1
#define INPUT_LAYER_GAME_SPEC 2

namespace inexor {
namespace ui {
namespace input {

class InputRouter
{
    public:
        InputRouter();
        virtual ~InputRouter();

        /// Check if key was pressed repeatedly using bit masking technique
        void keyrepeat(bool on, int mask);

        /// Start and stop accepting unicode text input events
        /// @see SDL_StartTextInput
        /// @see SDL_StopTextInput
        void textinput(bool on, int mask);

        /// Do grab the input depending on the current grab mode
        void inputgrab();

        /// Sets input grab mode for mouse and keyboard
        void set_grab_input(bool grab_input);

        /// "abort" key to interrupt updating the masterlist,
        /// connecting to a server or computing lightmaps
        bool interceptkey(int sym);

        /// @see SDL_PeepEvents
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
        /// @warning this is very technical OS-depending code
        bool filterevent(const SDL_Event &event);

        /// poll and filter all events in the SDL (input) event queue
        /// @see SDL_PollEvent
        /// @see filterevent
        bool pollevent(SDL_Event &event);

        /// move mouse to screen center
        /// @see SDL_WarpMouseInWindow
        void resetmousemotion();

        /// handle mouse motion coordinates
        /// @warning this is a call by reference function!
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

// Provide global exports

extern InputRouter input_router;
extern SharedVar<int> userelativemouse;

}
}
}
