#include "inexor/flowgraph/sleep/fl_sleep.hpp"

namespace inexor {
namespace vscript {


    CSleepNode::CSleepNode(vec position,
                           unsigned int sleeptime, 
                           const char* name, 
                           const char* comment)
    {
        sleep_interval = sleeptime;
        pos = position;
        sleep_active = false;
        default_box_color = VSCRIPT_COLOR_GRAY;
        node_name = name;
        node_comment = "[-]";
    }


    CSleepNode::~CSleepNode()
    {
    }



    void CSleepNode::in()
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
            sprintf(tmp, "%d/%d ms", time_left2sleep, sleep_interval);
            node_comment = tmp;

            // wait in 10 ms intervals
            SDL_Delay(10);
        }
        
        sprintf(tmp, "0/%d ms", sleep_interval);
        node_comment = tmp;
        box_color = VSCRIPT_COLOR_TRIGGERED;
        last_time = SDL_GetTicks();
        sleep_active = false;

        out();
    }

    
    bool CSleepNode::OnLinkAsChildNodeAttempt(CScriptNode* parent)
    {
        return true;
    }

    bool CSleepNode::OnLinkAsParentNodeAttempt(CScriptNode* child)
    {
        return true;
    }

};
};
