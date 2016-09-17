/// @file fl_event_player_enter_area.hpp
/// @author Johannes Schneider
/// @brief

#ifndef INEXOR_VSCRIPT_AREA_EVENT_HEADER
#define INEXOR_VSCRIPT_AREA_EVENT_HEADER

#include "inexor/flowgraph/events/base/fl_event_base.hpp"
#include "inexor/flowgraph/areas/box/fl_area_box.hpp"
#include "inexor/flowgraph/areas/cone/fl_area_cone.hpp"
#include "inexor/flowgraph/areas/cylinder/fl_area_cylinder.hpp"
#include "inexor/flowgraph/areas/sphere/fl_area_sphere.hpp"

namespace inexor {
namespace vscript {

    class CAreaEventNode : public CEventBaseNode
    {
        public:

            CAreaEventNode();
            ~CAreaEventNode();

            bool OnLinkAsChildNodeAttempt(CScriptNode*);
            bool OnLinkAsParentNodeAttempt(CScriptNode*);

        protected:

            // the area we are going to work with
            CScriptNode* area;
            INEXOR_VSCRIPT_NODE_TYPE area_type;

    };

};
};

#endif
