/// @file fl_sleep.h
/// @author Johannes Schneider
/// @brief Sleep functions represent pauses in a script. A sleep remains sleeping for {n} miliseconds.
/// 
/// .-------------------------------------------------------------------------------------------------.
/// | Sleep                                                                                           |
/// |_________________________________________________________________________________________________|
/// |                                                                                                 |
/// | Sleepers are script pausing functions which will wait for {n} miliseconds until script          |
/// | execution continues.                                                                            |
/// | Sleepers have the following members and methods which will be displayed in the node renderer:   |
/// |                                                                                                 |
/// | sleepstart          The time in miliseconds afert program start when sleeping began.            |
/// | sleepend            The time when sleeping will end.                                            |
/// | sleeptime           The amount of time to wait until script execution continues.                |
/// ._________________________________________________________________________________________________.
/// 

// Include guard
#ifndef INEXOR_VSCRIPT_SLEEP_HEADER
#define INEXOR_VSCRIPT_SLEEP_HEADER

#include "inexor/engine/engine.h"
#include "inexor/flowgraph/node/fl_nodebase.h"


// Inexor namespace protection
namespace inexor {
namespace vscript {

/// At least 10 ms of sleep
#define INEXOR_VSCRIPT_MIN_SLEEP_INTERVAL 10

/// One whole day is the maximum delay (in miliseconds)
#define INEXOR_VSCRIPT_MAX_SLEEP_INTERVAL 1000 * 60 * 60 * 24

/// @brief Implementation of timer nodes.
class sleep_node : public script_node
{
    public:
    
    // Please note: there is no standard constructor!

    /// Overloaded constructor for dynamic allocation
    sleep_node(vec pos, 
                unsigned int sleeptime, 
                const char* name = "NewTimer1", 
                const char* comment = "Hello World Comment", 
                INEXOR_VSCRIPT_TIME_FORMAT format = TIME_FORMAT_MILISECONDS);
                
    ~sleep_node();

    unsigned int sleep_start;
    unsigned int sleep_end;
    unsigned int sleep_interval;

    /// Incoming node signal
    void in();

    /// Implementation of the run method
    void run();
        
    /// Resetting the timer means to reset last_time
    void reset();

    private:
    
    /// notify child nodes
    void out();
};

// end of namespace
};
};

#endif
