/// @file fl_area_sphere.hpp
/// @author Johannes Schneider
/// @brief spheres are defined by position and radius

#ifndef INEXOR_VSCRIPT_AREA_SPHERE_HEADER
#define INEXOR_VSCRIPT_AREA_SPHERE_HEADER

#include "inexor/flowgraph/nodebase/fl_base.hpp"

namespace inexor {
namespace vscript {

    class CSphereAreaNode : public CScriptNode
    {
        protected:

            float sphere_radius;
            // TODO: make the render detail level dynamic
            const int render_detail_level = 50;

        public:

            CSphereAreaNode(vec, float);
            ~CSphereAreaNode();
            
            float get_radius();
            // render sphere around node box
            void render_additional();
            bool is_point_inside_sphere(vec);

            bool OnLinkAsChildNodeAttempt(CScriptNode*);
            bool OnLinkAsParentNodeAttempt(CScriptNode*);
    };

};
};

#endif
