/// @file fl_timer.h (flowgraph's timer implementation)
/// @author Johannes Schneider
/// @brief Timers will be called every [n] miliseconds

///  .-------------------------------------------------------------------------------------------------.
///  | Timer                                                                                           |
///  |_________________________________________________________________________________________________|
///  |                                                                                                 |
///  | A timer is a type of nodes which (beside events) can actually be the entry point of execution.  |
///  | Timers will be called every [clock_interval] miliseconds/seconds/minutes/hours.. and run code.  |
///  | Timers have the following members and methods will will be displayed by the node renderer       |
///  |                                                                                                 |
///  | inherited from script_node base class:                                                          |
///  | type         represents the type of the node (write protected)                                  |
///  | position     stands for the node's 3D position                                                  |
///  | active       indicates if this node is active                                                   |
///  | selected     indicates if this node is selected                                                 |
///  | node_name    the name of the node                                                               |
///  | node_comment the comment of the node                                                            |
///  |_________________________________________________________________________________________________|
///  |                                                                                                 |
///  | interval     the frequency with which this node will be called                                  |
///  | startdelay   the amount of time which has to pass until the first call will be done             |
///  | counter      how many times has this node already been called                                   |
///  ._________________________________________________________________________________________________.


// include guard
#ifndef INEXOR_VSCRIPT_TIMER_HEADER
#define INEXOR_VSCRIPT_TIMER_HEADER

#include "inexor/engine/engine.h"

/// project's namespace protection
namespace inexor {
namespace vscript {


/// minimal time interval
#define INEXOR_VSCRIPT_MIN_TIMER_INTERVAL 20

/// maximum time interval
/// one day is the maximum delay
#define INEXOR_VSCRIPT_MAX_TIMER_INTERVAL 1000 * 60 * 60 * 24


/// Implementation of timer nodes
class timer_node : public script_node
{
    public:

    /// overloaded constructor which passes timer interval
    timer_node(vec pos, unsigned int interval, unsigned int delay)
    {
        clamp(interval, INEXOR_VSCRIPT_MIN_TIMER_INTERVAL, INEXOR_VSCRIPT_MAX_TIMER_INTERVAL);
        position = pos;
        clock_interval = interval;
        start_delay = delay;
        last_time = SDL_GetTicks();
        activation_counter = 0;

        /// set the node's name
        node_name = "timer";

        /// set type
        type = NODE_TYPE_TIMER;
    }

    ~timer_node() {}

    /// timer related data
    /// time data in miliseconds
    unsigned int clock_interval;
    unsigned int start_delay;
    unsigned int last_time;
    unsigned int activation_counter;

    /// implementation of the run method
    /// which was declared as virtual in script_node
    void run()
    {
        /// set color to light blue
        glColor4f(0.0f, 148/255.0f, 1, 0.5);
        check_timer();
    }
    
    private:

    /// check the timer status
    /// do we need to call the trigger?
    void check_timer() 
    {
        unsigned int tmp = SDL_GetTicks();
        
        if(tmp - last_time >= clock_interval) 
        {
            /// trigger 
            trigger();
            /// save the timestamp
            last_time = SDL_GetTicks();
            /// increase activation counter
            activation_counter++;
        }

        /// yellow color effect is 100 ms long
        if(tmp - last_time < 100) glColor4f(1, 1, 0, 0.5);
    }

    /// event triggered
    void trigger()
    {
        //conoutf(CON_DEBUG, "trigger # %d", activation_counter);
        for(unsigned int i = 0; i < outgoing.size(); i++) {
            outgoing[i]->run();
        }
    }
};


// end of namespace
};
};

#endif
