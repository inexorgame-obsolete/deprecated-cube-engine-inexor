#include "inexor/flowgraph/sleep/fl_sleep.h"

namespace inexor {
namespace vscript {

    CSleepNode::CSleepNode(vec pos,
                           unsigned int sleeptime, 
                           const char* name, 
                           const char* comment)
    {
        sleep_interval = sleeptime;
        position = pos;
        sleep_active = false;
        default_box_color = VSCRIPT_COLOR_GRAY;
    }


    CSleepNode::~CSleepNode()
    {
    }


    void CSleepNode::run()
    {
        /// TODO: Implement multithreading?
        if(!sleep_active)
        {
            sleep_active = true;
            sleep_start = SDL_GetTicks();
            sleep_end = sleep_start + sleep_interval;
            box_color = default_box_color;
        }
        if(SDL_GetTicks() >= sleep_end)
        {
            box_color = VSCRIPT_COLOR_BLACK;
            last_time = SDL_GetTicks();
            sleep_active = false;
            out();
        }
    }

    
    void CSleepNode::reset()
    {
    }

};
};
