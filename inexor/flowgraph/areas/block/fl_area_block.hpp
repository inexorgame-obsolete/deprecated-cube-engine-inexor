/// @file fl_area_block.hpp
/// @author Johannes Schneider
/// @brief a block area is defined by position, width, height, and depth

// TODO: make block areas rotatable in at least one dimension

#ifndef INEXOR_VSCRIPT_AREA_BLOCK_HEADER
#define INEXOR_VSCRIPT_AREA_BLOCK_HEADER

#include "inexor/flowgraph/nodebase/fl_base.hpp"

namespace inexor {
namespace vscript {

    class CCubeAreaNode : public CScriptNode
    {
        protected:
            
            float box_width;
            float box_height;
            float box_depth;

        public:

            CCubeAreaNode(vec, float, float, float);
            ~CCubeAreaNode();
            
            bool is_point_inside_box(vec);

            void render_additional();

            bool OnLinkAsChildNodeAttempt(CScriptNode*);
            bool OnLinkAsParentNodeAttempt(CScriptNode*);
    };

};
};

#endif
