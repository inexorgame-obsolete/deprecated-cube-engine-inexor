/// @file fl_sleep.h
/// @author Johannes Schneider
/// @brief Sleeps wait a certain amount of miliseconds until their code execution continues.

#ifndef INEXOR_VSCRIPT_SLEEP_HEADER
#define INEXOR_VSCRIPT_SLEEP_HEADER

#include "inexor/engine/engine.h"
//#include "inexor/flowgraph/node/fl_nodebase.h"

#define INEXOR_VSCRIPT_MIN_SLEEP_INTERVAL 5 // 10ms
#define INEXOR_VSCRIPT_MAX_SLEEP_INTERVAL 1000 * 60 * 60 * 24 // 1 day


namespace inexor {
namespace vscript {

    class CSleepNode : public CScriptNode
    {
        public:
    
            unsigned int sleep_start;
            unsigned int sleep_end;
            unsigned int sleep_interval;
            bool         sleep_active;

            
            CSleepNode(vec pos,
                       unsigned int sleeptime,
                       const char* name = "NewSleep1",
                       const char* comment = "Hello World Comment for a Sleep");
                
            ~CSleepNode();

            void run();
            void reset();
    };

};
};

#endif
