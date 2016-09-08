/// @file fl_event_player_enter_area.hpp
/// @author Johannes Schneider
/// @brief When a player enters an area this event will be triggered

#ifndef INEXOR_VSCRIPT_EVENT_PLAYER_ENTER_AREA_HEADER
#define INEXOR_VSCRIPT_EVENT_PLAYER_ENTER_AREA_HEADER

#include "inexor/flowgraph/events/base/fl_event_base.hpp"

// area types
#include "inexor/flowgraph/areas/block/fl_area_block.hpp"
#include "inexor/flowgraph/areas/cone/fl_area_cone.hpp"
#include "inexor/flowgraph/areas/cylinder/fl_area_cylinder.hpp"
#include "inexor/flowgraph/areas/sphere/fl_area_sphere.hpp"

namespace inexor {
namespace vscript {

    // TODO: divide into "CPlayerAreaEventBaseNode" class!!
    class CPlayerEnterAreaEventNode : public CEventBaseNode
    {
        public:

            CPlayerEnterAreaEventNode(vec);
            ~CPlayerEnterAreaEventNode();

            // TODO: enum type them!

            // TODO: union them!
            CScriptNode* area;
            INEXOR_VSCRIPT_NODE_TYPE area_type;

            void in();
            void check_trigger();
            void out();

            bool OnLinkAsChildNodeAttempt(CScriptNode* parent);
            bool OnLinkAsParentNodeAttempt(CScriptNode* child);
    };

};
};

#endif
