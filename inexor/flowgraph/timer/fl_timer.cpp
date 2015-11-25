#include "inexor/flowgraph/timer/fl_timer.h"

namespace inexor {
namespace vscript {


    CTimerNode::CTimerNode(vec pos, unsigned int interval, unsigned int startdelay, unsigned int limit, unsigned int cooldown, const char* name, const char* comment, INEXOR_VSCRIPT_TIME_FORMAT format)
    {
        position = pos;
        node_name = name;
        node_comment = comment;
        
        /// convert the time format
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


    void CTimerNode::run()
    {
        check_if_execution_is_due();
    }


    /// resetting the timer means to reset last_time
    void CTimerNode::reset()
    {
        /// TODO: do we need this?
        last_time = 0;
    }

    /// decide if we need to run the code
    void CTimerNode::check_if_execution_is_due() 
    {
        /// render color effects
        if(this_time - last_time < INEXOR_VSCRIPT_ACTIVE_NODE_TIMER_INTERVAL) box_color = VSCRIPT_COLOR_TRIGGERED;
        else box_color = VSCRIPT_COLOR_TIMER;

        if(this_time - last_time >= timer_interval) 
        {
            CScriptNode::out();
            last_time = this_time;
            timer_counter++;
        }

        /// TODO: implement cooldown!
    }


/// end of namespace
};
};
