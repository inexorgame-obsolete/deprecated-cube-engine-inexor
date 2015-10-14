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

#include "inexor/flowgraph/node/fl_nodebase.h"
#include "inexor/engine/engine.h"

// Inexor namespace protection
namespace inexor {
namespace vscript {


/// TODO: undefine once debugging is finished
//#define INEXOR_VSCRIPT_DEBUG_TIMERS

/// minimum time interval (in miliseconds)
#define INEXOR_VSCRIPT_MIN_TIMER_INTERVAL 10

/// one whole day is the maximum delay (in miliseconds)
#define INEXOR_VSCRIPT_MAX_TIMER_INTERVAL 1000 * 60 * 60 * 24

/// blink every 100 miliseconds
#define VSCRIPT_ACTIVE_NODE_TIMER_INTERVAL 100


/// time format enumerations
enum INEXOR_VSCRIPT_TIMER_FORMAT
{
    TIMER_FORMAT_MILISECONDS,
    TIMER_FORMAT_SECONDS,
    TIMER_FORMAT_MINUTES,
    TIMER_FORMAT_HOURS
};

/// @brief Implementation of timer nodes.
class timer_node : public script_node
{
    public:
    
    // Please note: there is no standard constructor!

    /// Overloaded constructor for dynamic allocation
    timer_node(vec pos, unsigned int interval, unsigned int startdelay, unsigned int limit = 1000*1000, unsigned int cooldown = 0, const char* name = "a timer", const char* comment = "hello world comment", INEXOR_VSCRIPT_TIMER_FORMAT format = TIMER_FORMAT_MILISECONDS);

    ~timer_node();

    /// Timer related data
    /// Time data in miliseconds
    unsigned int timer_startdelay;
    unsigned int timer_counter;
    unsigned int timer_interval;
    unsigned int timer_limit;
    unsigned int timer_cooldown;

    /// Incoming node signal
    void in();

    /// Implementation of the run method
    void run();
        
    /// Resetting the timer means to reset last_time
    void reset();

    private:

    /// check the timer status
    /// do we need to call the trigger?
    void check_if_execution_is_due();

    /// notify child nodes
    void out();
};

// end of namespace
};
};

#endif
