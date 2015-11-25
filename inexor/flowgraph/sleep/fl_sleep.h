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

/// At least 10 ms of sleep
#define INEXOR_VSCRIPT_MIN_SLEEP_INTERVAL 10

/// One whole day is the maximum delay (in miliseconds)
#define INEXOR_VSCRIPT_MAX_SLEEP_INTERVAL 1000 * 60 * 60 * 24

// Inexor namespace protection
namespace inexor {
namespace vscript {

    /// @brief Implementation of timer nodes.
    class CSleepNode : public CScriptNode
    {
        public:
    
            unsigned int sleep_start;
            unsigned int sleep_end;
            unsigned int sleep_interval;

            CSleepNode(vec pos, 
                       unsigned int sleeptime, 
                       const char* name = "NewSleep1", 
                       const char* comment = "Hello World Sleep");
                
            ~CSleepNode();

            void run();
    };


// end of namespace
};
};

#endif
