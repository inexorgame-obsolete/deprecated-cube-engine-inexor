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
        node_name = name;
        //node_comment = comment;
    }


    CSleepNode::~CSleepNode()
    {
    }


    void CSleepNode::run()
    {
        char tmp[64];
        unsigned int time_left2sleep = sleep_end - SDL_GetTicks();
        sprintf(tmp, "waiting %dms", time_left2sleep);
        node_name = tmp;

        if(!sleep_active)
        {
            sleep_active = true;
            sleep_start = SDL_GetTicks();
            sleep_end = sleep_start + sleep_interval;
            box_color = default_box_color;
        }
        else 
        {   
            if(SDL_GetTicks() >= sleep_end)
            {
                box_color = VSCRIPT_COLOR_TRIGGERED;
                last_time = SDL_GetTicks();
                sleep_active = false;
                out();
            }
        }
    }

    
    void CSleepNode::reset()
    {
    }

};
};
