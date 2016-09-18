#include "inexor/flowgraph/sleep/fl_sleep.hpp"

namespace inexor {
namespace vscript {

    CSleepNode::CSleepNode(vec position, unsigned int sleeptime)
    {
        type = INEXOR_VSCRIPT_NODE_TYPE_SLEEP;
        sleep_interval = clamp(sleeptime, INEXOR_VSCRIPT_MIN_SLEEP_INTERVAL, INEXOR_VSCRIPT_MAX_SLEEP_INTERVAL);
        pos = position;
        sleep_active = false;
        default_box_color = INEXOR_VSCRIPT_COLOR_FUNCTION;
        box_color = default_box_color;
        char tmp[64];
        std::snprintf(tmp, 64, "0/%d ms", sleep_interval);
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

        // the default color must be changed so color effects can be rendered
        // correctly by render_nodes()
        default_box_color = INEXOR_VSCRIPT_COLOR_PENDING;

        while(sleep_end >= SDL_GetTicks())
        {
            int time_left2sleep = sleep_end - SDL_GetTicks();
            if(time_left2sleep < 0) time_left2sleep = 0;
            sprintf(tmp, "%d/%d ms", time_left2sleep, sleep_interval);
            node_comment = tmp;
            SDL_Delay(10);
        }
        
        sprintf(tmp, "0/%d ms", sleep_interval);
        node_comment = tmp;

        default_box_color = INEXOR_VSCRIPT_COLOR_FUNCTION;
        box_color = INEXOR_VSCRIPT_COLOR_TRIGGERED;
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
