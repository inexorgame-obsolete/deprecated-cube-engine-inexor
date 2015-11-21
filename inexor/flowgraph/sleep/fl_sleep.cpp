#include "inexor/flowgraph/sleep/fl_sleep.h"

namespace inexor {
namespace vscript {

    sleep_node::sleep_node(vec pos, 
                           unsigned int sleeptime, 
                           const char* name, 
                           const char* comment)
    {
        sleep_interval = sleeptime;
    }


    sleep_node::~sleep_node()
    {
    }


    void sleep_node::in()
    {
        /// save the current time
        sleep_start = SDL_GetTicks();
        sleep_end = sleep_start + sleep_interval;
        run();
    }


    void sleep_node::run()
    {
        /// call outgoing method once waiting has finished
        /// TODO: multithreading?
        if(SDL_GetTicks() >= sleep_end)
        {
            out();
        }
    }


    void sleep_node::out()
    {
        particle_text(position + vec(boxsize/2, boxsize/2, 0.0f), "go!", PART_TEXT, 5000, 0x32FF00, 2.0f, -10.0f);
        /// run child node's code
        for(unsigned int i = 0; i < outgoing.size(); i++) outgoing[i]->in();
    }


    void sleep_node::reset()
    {
    }


/// end of namespace
};
};
