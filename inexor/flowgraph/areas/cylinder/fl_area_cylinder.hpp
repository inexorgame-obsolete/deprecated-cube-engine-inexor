/// @file fl_area_cylinder.hpp
/// @author Johannes Schneider
/// @brief areas are used for events based on the interactions with them.

#ifndef INEXOR_VSCRIPT_AREA_CYLINDER_HEADER
#define INEXOR_VSCRIPT_AREA_CYLINDER_HEADER

#include "inexor/flowgraph/nodebase/fl_base.hpp"

namespace inexor {
namespace vscript {

    class CCylinderAreaNode : public CScriptNode
    {
        protected:
            
            float cylinder_height;
            float cylinder_radius;
            const int render_detail_level = 30;

        public:

            CCylinderAreaNode(vec, float, float);
            ~CCylinderAreaNode();
            
            void render_additional();

            bool OnLinkAsChildNodeAttempt(CScriptNode*);
            bool OnLinkAsParentNodeAttempt(CScriptNode*);
    };

};
};

#endif
