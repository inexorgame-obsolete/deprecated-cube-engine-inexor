/// @file fl_timer.h
/// @author Johannes Schneider
/// @brief Timers will execute code in a very certain interval of {n} miliseconds/seconds/minutes/hours.
/// 
/// .-------------------------------------------------------------------------------------------------.
/// | Timer                                                                                           |
/// |_________________________________________________________________________________________________|
/// |                                                                                                 |
/// | A timer is a type of nodes which (beside events) can actually be the entry point of execution.  |
/// | Timers will be called every [clock_interval] miliseconds/seconds/minutes/hours and run code.    |
/// | Timers have the following members and methods will will be displayed by the node renderer:      |
/// |                                                                                                 |
/// | interval     the frequency with which this node will execute code                               |
/// | startdelay   the amount of time which has to pass until the first call will be done.            |
/// |              the start delay begins with the end of the script's loading process.               |
/// | counter      how many times has this node already been called (write protected).                |
/// | limiter      the maximum amount of executions until the cooldown lock will be activated.        |
/// | cooldown     the amount of time which has to pass when counter exceeds the limiter.             |
/// ._________________________________________________________________________________________________.
/// 

// Include guard
#ifndef INEXOR_VSCRIPT_TIMER_HEADER
#define INEXOR_VSCRIPT_TIMER_HEADER

#include "inexor/engine/engine.h"
#include "inexor/flowgraph/node/fl_nodebase.h"

/// time conversion
#include "inexor/flowgraph/time/fl_timetools.h"

/// Minimum time interval (in miliseconds)
#define INEXOR_VSCRIPT_MIN_TIMER_INTERVAL 10

/// One whole day is the maximum delay (in miliseconds)
#define INEXOR_VSCRIPT_MAX_TIMER_INTERVAL 1000 * 60 * 60 * 24

/// Blink every 100 miliseconds
#define INEXOR_VSCRIPT_ACTIVE_NODE_TIMER_INTERVAL 100

/// Default timer execution limit
#define INEXOR_VSCRIPT_DEFAULT_TIMER_EXECUTION_LIMIT 1000*1000


// Inexor namespace protection
namespace inexor {
namespace vscript {

    /// @brief Implementation of timer nodes.
    class timer_node : public script_node
    {
        public:

        timer_node(vec pos, 
                    unsigned int interval, 
                    unsigned int startdelay, 
                    unsigned int limit = INEXOR_VSCRIPT_DEFAULT_TIMER_EXECUTION_LIMIT, 
                    unsigned int cooldown = 0, 
                    const char* name = "NewTimer1", 
                    const char* comment = "Hello World Comment", 
                    INEXOR_VSCRIPT_TIME_FORMAT format = TIME_FORMAT_MILISECONDS);


        ~timer_node();

        unsigned int timer_startdelay;
        unsigned int timer_counter;
        unsigned int timer_interval;
        unsigned int timer_limit;
        unsigned int timer_cooldown;

        void in();
        void run();
        void reset();


        private:

        /// check the timer status
        /// do we need to call the trigger?
        void check_if_execution_is_due();

        void out();
    };


// end of namespace
};
};

#endif
