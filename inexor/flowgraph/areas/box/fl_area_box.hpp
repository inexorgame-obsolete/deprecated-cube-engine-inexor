/// @file fl_area_block.hpp
/// @author Johannes Schneider
/// @brief areas are used for events based on the interactions with them.

#ifndef INEXOR_VSCRIPT_AREA_BLOCK_HEADER
#define INEXOR_VSCRIPT_AREA_BLOCK_HEADER

#include "inexor/flowgraph/nodebase/fl_base.hpp"
#include "inexor/fpsgame/game.hpp"
#include "inexor/util/Logging.hpp"

namespace inexor {
namespace vscript {

    #define INEXOR_VSCRIPT_BOX_AREA_MIN_BOX_SIZE 16
    #define INEXOR_VSCRIPT_BOX_AREA_MAX_BOX_SIZE 8192

    class CBoxAreaNode : public CScriptNode
    {
        protected:
            
            float box_width;
            float box_height;
            float box_depth;

            // a box does not have a render detail level

        public:

            CBoxAreaNode(const vec, const float, const float, const float);
            ~CBoxAreaNode();
            
            void render_additional();
            bool is_point_inside_box(const vec);

            bool OnLinkAsChildNodeAttempt(CScriptNode*);
            bool OnLinkAsParentNodeAttempt(CScriptNode*);
    };

};
};

#endif
