/// @file fl_area_sphere.hpp
/// @author Johannes Schneider
/// @brief areas are used for events based on the interactions with them.

#ifndef INEXOR_VSCRIPT_AREA_SPHERE_HEADER
#define INEXOR_VSCRIPT_AREA_SPHERE_HEADER

#include "inexor/flowgraph/nodebase/fl_base.hpp"
#include "inexor/fpsgame/game.hpp"

namespace inexor {
namespace vscript {

    class CSphereAreaNode : public CScriptNode
    {
        protected:

            float sphere_radius;
            const int render_detail_level = INEXOR_VSCRIPT_DEFAULT_RENDER_DETAIL_LEVEL;

        public:

            CSphereAreaNode(const vec, const float);
            ~CSphereAreaNode();
            
            void render_additional();
            bool is_point_inside_sphere(const vec);
            float get_radius();

            bool OnLinkAsChildNodeAttempt(CScriptNode*);
            bool OnLinkAsParentNodeAttempt(CScriptNode*);
    };

};
};

#endif
