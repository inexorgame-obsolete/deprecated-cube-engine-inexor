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
        node_comment = "[-]";
    }


    CSleepNode::~CSleepNode()
    {
    }



    void CSleepNode::run()
    {
        char tmp[64];
        sleep_active = true;
        sleep_start = SDL_GetTicks();
        sleep_end = sleep_start + sleep_interval;
        box_color = default_box_color;
        
        while(sleep_end >= SDL_GetTicks())
        {
            int time_left2sleep = sleep_end - SDL_GetTicks();
            if(time_left2sleep < 0) time_left2sleep =0;
            sprintf(tmp, "[waiting %dms]", time_left2sleep);
            node_comment = tmp;

            SDL_Delay(5);
        }
        
        sprintf(tmp, "[-]");
        node_comment = tmp;
        box_color = VSCRIPT_COLOR_TRIGGERED;
        last_time = SDL_GetTicks();
        sleep_active = false;
        out();
    }

    
    void CSleepNode::reset()
    {
    }

};
};
