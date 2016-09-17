/// @file fl_area_block.hpp
/// @author Johannes Schneider
/// @brief areas are used for events based on the interactions with them.

#ifndef INEXOR_VSCRIPT_AREA_CONE_HEADER
#define INEXOR_VSCRIPT_AREA_CONE_HEADER

#include "inexor/flowgraph/nodebase/fl_base.hpp"

namespace inexor {
namespace vscript {

    class CConeAreaNode : public CScriptNode
    {
        protected:
            
            float cone_height;
            float cone_radius;
            const int render_detail_level = INEXOR_VSCRIPT_DEFAULT_RENDER_DETAIL_LEVEL;

        public:

            CConeAreaNode(const vec, const float, const float);
            ~CConeAreaNode();
            
            void render_additional();

            bool OnLinkAsChildNodeAttempt(CScriptNode*);
            bool OnLinkAsParentNodeAttempt(CScriptNode*);
    };

};
};

#endif
