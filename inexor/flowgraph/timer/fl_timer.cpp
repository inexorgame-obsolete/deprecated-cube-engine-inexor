#include "inexor/flowgraph/timer/fl_timer.h"

namespace inexor {
namespace vscript {


    CTimerNode::CTimerNode(vec position, 
                           unsigned int interval, 
                           unsigned int startdelay, 
                           unsigned int limit, 
                           unsigned int cooldown, 
                           const char* name, 
                           const char* comment, 
                           INEXOR_VSCRIPT_TIME_FORMAT format)
    {
        pos = position;
        node_name = name;
        node_comment = comment;
        
        /// TODO: convert the time format
        unsigned int time_format_in_ms = interval; //ConvertTime2Miliseconds(interval, format);

        /// cut the timer interval
        clamp(interval, INEXOR_VSCRIPT_MIN_TIMER_INTERVAL, INEXOR_VSCRIPT_MAX_TIMER_INTERVAL);
        timer_interval = time_format_in_ms;
        timer_startdelay = startdelay;
        timer_limit = limit;
        timer_cooldown = cooldown;
        last_time = SDL_GetTicks();
        timer_counter = 0;
        type = NODE_TYPE_TIMER;
    }


    CTimerNode::~CTimerNode()
    {
    }

    
    void CTimerNode::in()
    {
        run();
    }


    void CTimerNode::run()
    {
        check_if_execution_is_due();
    }


    void CTimerNode::reset()
    {
        last_time = 0;
    }


    static int LetsGo(void *ptr)
    {
        CScriptNode *node = static_cast<CScriptNode*>(ptr);
        if(nullptr != node) node->in();
        return 0;
    }


    // decide if we need to run the code
    void CTimerNode::check_if_execution_is_due() 
    {
        if(this_time - last_time >= timer_interval) 
        {
            for(unsigned int i=0; i<children.size(); i++)
            {
                conoutf(CON_DEBUG, "thread started!");
                SDL_Thread *thread = SDL_CreateThread(LetsGo, "LetsGo", (void *)children[i]);
            }
            last_time = this_time;
            timer_counter++;
        }
    }

};
};
