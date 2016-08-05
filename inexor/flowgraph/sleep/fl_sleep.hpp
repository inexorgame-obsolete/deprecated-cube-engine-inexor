/// @file fl_sleep.hpp
/// @author Johannes Schneider
/// @brief wait some miliseconds until the code execution continues

#ifndef INEXOR_VSCRIPT_SLEEP_HEADER
#define INEXOR_VSCRIPT_SLEEP_HEADER

#include "inexor/flowgraph/nodebase/fl_base.hpp"

#define INEXOR_VSCRIPT_MIN_SLEEP_INTERVAL 5
#define INEXOR_VSCRIPT_MAX_SLEEP_INTERVAL 1000 * 60 * 60 * 24  // 1 day


namespace inexor {
namespace vscript {

    class CSleepNode : public CScriptNode
    {
        public:

            unsigned int sleep_start;
            unsigned int sleep_end;
            unsigned int sleep_interval;
            bool         sleep_active;

            CSleepNode(vec pos, unsigned int sleeptime);
            ~CSleepNode();
            
            void in();

            bool OnLinkAsChildNodeAttempt(CScriptNode* parent);
            bool OnLinkAsParentNodeAttempt(CScriptNode* child);
    };

};
};

#endif
