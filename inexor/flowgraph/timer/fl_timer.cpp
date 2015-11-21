#include "inexor/flowgraph/timer/fl_timer.h"

namespace inexor {
namespace vscript {


    timer_node::timer_node(vec pos, unsigned int interval, unsigned int startdelay, unsigned int limit, unsigned int cooldown, const char* name, const char* comment, INEXOR_VSCRIPT_TIME_FORMAT format)
    {
        position = pos;
        node_name = name;
        node_comment = comment;
        
        /// convert the time format
        unsigned int time_format_in_ms = ConvertTimeToMiliseconds(interval, format);

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


    timer_node::~timer_node()
    {
    }

    
    void timer_node::in()
    {
        run();
    }


    void timer_node::run()
    {
        check_if_execution_is_due();
    }


    /// Resetting the timer means to reset last_time
    void timer_node::reset()
    {
        /// TODO: do we need this?
        last_time = 0;
    }


    /// decide if we need to run the code
    void timer_node::check_if_execution_is_due() 
    {
        /// render color effects
        if(this_time - last_time < INEXOR_VSCRIPT_ACTIVE_NODE_TIMER_INTERVAL) box_color = VSCRIPT_COLOR_TRIGGERED;
        else box_color = VSCRIPT_COLOR_TIMER;

        if(this_time - last_time >= timer_interval) 
        {
            out();
            last_time = this_time;
            timer_counter++;
        }

        /// TODO: implement cooldown!
    }


    void timer_node::out()
    {
        particle_text(position + vec(boxsize/2, boxsize/2, 0.0f), "go!", PART_TEXT, 5000, 0x32FF00, 2.0f, -10.0f);
        /// run child node's code
        for(unsigned int i = 0; i < outgoing.size(); i++) outgoing[i]->in();
    }

/// end of namespace
};
};
