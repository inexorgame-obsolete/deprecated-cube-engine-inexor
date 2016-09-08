/// @file fl_event_player_enter_area.hpp
/// @author Johannes Schneider
/// @brief When a player enters an area this event will be triggered

#ifndef INEXOR_VSCRIPT_AREA_EVENT_PLAYER_ENTER_HEADER
#define INEXOR_VSCRIPT_AREA_EVENT_PLAYER_ENTER_HEADER

#include "inexor/flowgraph/events/areas/base/fl_area_event_base.hpp"

namespace inexor {
namespace vscript {

    class CPlayerEnterAreaEventNode : public CAreaEventNode
    {
        public:

            CPlayerEnterAreaEventNode(vec);
            ~CPlayerEnterAreaEventNode();
    
            void in();
            void check_trigger();
            void out();

            //bool OnLinkAsChildNodeAttempt(CScriptNode* parent);
            //bool OnLinkAsParentNodeAttempt(CScriptNode* child);

        protected:

    };

};
};

#endif
