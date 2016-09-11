/// @file fl_area_block.hpp
/// @author Johannes Schneider
/// @brief areas are used for events based on the interactions with them.

#ifndef INEXOR_VSCRIPT_AREA_BLOCK_HEADER
#define INEXOR_VSCRIPT_AREA_BLOCK_HEADER

#include "inexor/flowgraph/nodebase/fl_base.hpp"

namespace inexor {
namespace vscript {

    class CBoxAreaNode : public CScriptNode
    {
        protected:
            
            float box_width;
            float box_height;
            float box_depth;

            // a box does not have a render detail level

        public:

            CBoxAreaNode(vec, float, float, float);
            ~CBoxAreaNode();
            
            void render_additional();
            bool is_point_inside_box(vec);

            bool OnLinkAsChildNodeAttempt(CScriptNode*);
            bool OnLinkAsParentNodeAttempt(CScriptNode*);
    };

};
};

#endif
