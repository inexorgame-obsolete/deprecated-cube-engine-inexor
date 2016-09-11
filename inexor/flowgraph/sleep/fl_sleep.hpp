/// @file fl_sleep.hpp
/// @author Johannes Schneider
/// @brief sleep nodes delay code execution intentionally.

#ifndef INEXOR_VSCRIPT_SLEEP_HEADER
#define INEXOR_VSCRIPT_SLEEP_HEADER

#include "inexor/flowgraph/nodebase/fl_base.hpp"


namespace inexor {
namespace vscript {

    #define INEXOR_VSCRIPT_MIN_SLEEP_INTERVAL 10
    #define INEXOR_VSCRIPT_MAX_SLEEP_INTERVAL 1000 * 60 * 60 * 24  // 1 day

    class CSleepNode : public CScriptNode
    {
        public:

            CSleepNode(vec, unsigned int);
            ~CSleepNode();
            
            void in();

            bool OnLinkAsChildNodeAttempt(CScriptNode*);
            bool OnLinkAsParentNodeAttempt(CScriptNode*);
        
        protected:

            unsigned int sleep_start;
            unsigned int sleep_end;
            unsigned int sleep_interval;
            bool sleep_active;

    };

};
};

#endif
