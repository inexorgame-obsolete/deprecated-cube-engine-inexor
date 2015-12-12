// @file fl_timer.h
// @author Johannes Schneider
// @brief Timers will execute code in a very certain interval of {n} miliseconds/seconds/minutes/hours.

#ifndef INEXOR_VSCRIPT_TIMER_HEADER
#define INEXOR_VSCRIPT_TIMER_HEADER

#include "inexor/engine/engine.h"
#include "inexor/flowgraph/node/fl_nodebase.h"
#include "inexor/flowgraph/time/fl_timetools.h"

#define INEXOR_VSCRIPT_MIN_TIMER_INTERVAL 10
#define INEXOR_VSCRIPT_MAX_TIMER_INTERVAL 1000 * 60 * 60 * 24
#define INEXOR_VSCRIPT_ACTIVE_NODE_TIMER_INTERVAL 100
#define INEXOR_VSCRIPT_DEFAULT_TIMER_EXECUTION_LIMIT 1000*1000


namespace inexor {
namespace vscript {

    enum INEXOR_VSCRIPT_TIME_FORMAT
    {
        TIME_FORMAT_MILISECONDS,
        TIME_FORMAT_SECONDS,
        TIME_FORMAT_MINUTES,
        TIME_FORMAT_HOURS
    };

    /*unsigned int ConvertTime2Miliseconds(unsigned int interval, INEXOR_VSCRIPT_TIME_FORMAT format)
    {
        /// convert the interval into miliseconds
        switch(format)
        {
            case TIME_FORMAT_HOURS:
                interval *= 1000 * 60 *60;
                break;
            case TIME_FORMAT_MINUTES:
                interval *= 1000 * 60;
                break;
            case TIME_FORMAT_SECONDS:
                interval *= 1000;
                break;
            case TIME_FORMAT_MILISECONDS: 
                /// the engine's standard time format is miliseconds
                break;
        }
        return interval;
    }
    */

    class CTimerNode : public CScriptNode
    {
        private:

            void check_if_execution_is_due();
            void out();

        public:

            CTimerNode(vec pos, 
                        unsigned int interval, 
                        unsigned int startdelay, 
                        unsigned int limit = INEXOR_VSCRIPT_DEFAULT_TIMER_EXECUTION_LIMIT, 
                        unsigned int cooldown = 0, 
                        const char* name = "NewTimer1", 
                        const char* comment = "Hello World Comment", 
                        INEXOR_VSCRIPT_TIME_FORMAT format = TIME_FORMAT_MILISECONDS);

            ~CTimerNode();

            unsigned int timer_startdelay;
            unsigned int timer_counter;
            unsigned int timer_interval;
            unsigned int timer_limit;
            unsigned int timer_cooldown;

            void run();
            void reset();
    };

};
};

#endif
