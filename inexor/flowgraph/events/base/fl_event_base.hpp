/// @file fl_events.hpp
/// @author Johannes Schneider
/// @brief CEventBaseNode is a base class for events.

#ifndef INEXOR_VSCRIPT_EVENT_BASE_HEADER
#define INEXOR_VSCRIPT_EVENT_BASE_HEADER

#include "inexor/flowgraph/nodebase/fl_base.hpp"

namespace inexor {
namespace vscript {

    /// @brief every event node will be specified 
    /// as one of the following event types
    enum INEXOR_VSCRIPT_EVENT_TYPE
    {
        INEXOR_VSCRIPT_EVENT_TYPE_PLAYER_ENTER_AREA = 0,
        INEXOR_VSCRIPT_EVENT_TYPE_PLAYER_LEAVE_AREA,
        INEXOR_VSCRIPT_EVENT_TYPE_PLAYER_SUICIDE,
        INEXOR_VSCRIPT_EVENT_TYPE_PLAYER_SPAWN,
        INEXOR_VSCRIPT_EVENT_TYPE_PLAYER_SHOT,
    };


    class CEventBaseNode : public CScriptNode
    {
        public:

            CEventBaseNode();
            ~CEventBaseNode();

            void check_trigger();
                        
            INEXOR_VSCRIPT_EVENT_TYPE get_event_type();

        protected:

            INEXOR_VSCRIPT_EVENT_TYPE event_type;

    };

};
};

#endif
