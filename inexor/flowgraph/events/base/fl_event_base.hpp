/// @file fl_events.hpp
/// @author Johannes Schneider
/// @brief Base class for event management

#ifndef INEXOR_VSCRIPT_EVENT_BASE_HEADER
#define INEXOR_VSCRIPT_EVENT_BASE_HEADER

#include "inexor/flowgraph/nodebase/fl_base.hpp"

enum INEXOR_VSCRIPT_EVENT_TYPE
{
    INEXOR_VSCRIPT_EVENT_TYPE_PLAYER_ENTER_AREA = 0,
    INEXOR_VSCRIPT_EVENT_TYPE_PLAYER_LEAVE_AREA,
    INEXOR_VSCRIPT_EVENT_TYPE_PLAYER_SUICIDE,
    INEXOR_VSCRIPT_EVENT_TYPE_PLAYER_SPAWN,
    INEXOR_VSCRIPT_EVENT_TYPE_PLAYER_SHOT,
};


namespace inexor {
namespace vscript {

    class CEventBaseNode : public CScriptNode
    {
        public:

            CEventBaseNode();
            ~CEventBaseNode();

            void check_trigger();

            bool OnLinkAsChildNodeAttempt(CScriptNode* parent);
            bool OnLinkAsParentNodeAttempt(CScriptNode* child);
            
            INEXOR_VSCRIPT_EVENT_TYPE get_event_type();

        protected:

            INEXOR_VSCRIPT_EVENT_TYPE event_type;

    };

};
};

#endif
