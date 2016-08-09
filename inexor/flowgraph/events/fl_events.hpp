/// @file fl_events.hpp
/// @author Johannes Schneider
/// @brief Base class for event management

#ifndef INEXOR_VSCRIPT_EVENT_BASE_HEADER
#define INEXOR_VSCRIPT_EVENT_BASE_HEADER

#include "inexor/flowgraph/nodebase/fl_base.hpp"

enum INEXOR_VSCRIPT_EVENT_TYPE
{
    INEXOR_VSCRIPT_PLAYER_ENTERS_AREA,
    INEXOR_VSCRIPT_PLAYER_LEAVES_AREA,
    INEXOR_VSCRIPT_PLAYER_DEATH,
    INEXOR_VSCRIPT_PLAYER_SPAWN,
    INEXOR_VSCRIPT_PLAYER_SHOT,
};

namespace inexor {
namespace vscript {

    class CEventNodeBase : public CScriptNode
    {
        public:

            CEventNodeBase();
            ~CEventNodeBase();

            void in();
            void check_for_event_triggered();
            void out();

            bool OnLinkAsChildNodeAttempt(CScriptNode* parent);
            bool OnLinkAsParentNodeAttempt(CScriptNode* child);

        protected:


    };

};
};

#endif
