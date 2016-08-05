// @file fl_timer.hpp
// @author Johannes Schneider
// @brief timers will start to execute code in a very certain interval of {n} miliseconds/seconds/minutes/hours

#ifndef INEXOR_VSCRIPT_TIMER_HEADER
#define INEXOR_VSCRIPT_TIMER_HEADER

#include "inexor/flowgraph/nodebase/fl_base.hpp"

#define INEXOR_VSCRIPT_MIN_TIMER_INTERVAL              5
#define INEXOR_VSCRIPT_MAX_TIMER_INTERVAL              1000 * 60 * 60 * 24 // 1 day
#define INEXOR_VSCRIPT_ACTIVE_NODE_TIMER_INTERVAL      200 // render a color effect after a timer has been triggered
#define INEXOR_VSCRIPT_DEFAULT_TIMER_EXECUTION_LIMIT   1000*1000

#define INEXOR_VSCRIPT_TIMER_DEBUGGING 1

namespace inexor {
namespace vscript {

    enum INEXOR_VSCRIPT_TIME_FORMAT
    {
        INEXOR_VSCRIPT_TIME_FORMAT_MILISECONDS,
        INEXOR_VSCRIPT_TIME_FORMAT_SECONDS,
        INEXOR_VSCRIPT_TIME_FORMAT_MINUTES,
        INEXOR_VSCRIPT_TIME_FORMAT_HOURS
    };

    class CTimerNode : public CScriptNode
    {
        private:

            void check_if_execution_is_due();

        public:

            CTimerNode(vec pos, unsigned int interval, unsigned int startdelay,
                       unsigned int limit = INEXOR_VSCRIPT_DEFAULT_TIMER_EXECUTION_LIMIT,
                       unsigned int cooldown = 0, INEXOR_VSCRIPT_TIME_FORMAT format = INEXOR_VSCRIPT_TIME_FORMAT_MILISECONDS);
            ~CTimerNode();

            unsigned int timer_startdelay;
            unsigned int timer_counter;
            unsigned int timer_interval;
            unsigned int timer_limit;
            unsigned int timer_cooldown;

            void in();
            void reset();

            void render_additional(vec);

            bool OnLinkAsChildNodeAttempt(CScriptNode*);
            bool OnLinkAsParentNodeAttempt(CScriptNode*);
    };

};
};

#endif
