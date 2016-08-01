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

            float radius;
            const int circle_detail_level = 60;

        public:

            CSphereAreaNode(vec, float, const char*, const char*);
            ~CSphereAreaNode();
            
            bool collide(vec p);
            void render_additional();

            bool OnLinkAsChildNodeAttempt(CScriptNode* parent);
            bool OnLinkAsParentNodeAttempt(CScriptNode* child);
    };

};
};

#endif
