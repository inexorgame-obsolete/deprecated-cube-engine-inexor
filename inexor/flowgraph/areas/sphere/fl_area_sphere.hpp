/// @file fl_area_sphere.h
/// @author Johannes Schneider
/// @brief 

#ifndef INEXOR_VSCRIPT_AREA_SPHERE_HEADER
#define INEXOR_VSCRIPT_AREA_SPHERE_HEADER

#include "inexor/flowgraph/nodebase/fl_base.hpp"


namespace inexor {
namespace vscript {

    class CSphereAreaNode : public CScriptNode
    {
        public:

            // the distance from this vector to the position defines the radius of the sphere.
            vec radius;

            CSphereAreaNode(vec,vec,const char*,const char*);
            ~CSphereAreaNode();
            
            void render(int,bool);
            bool collide(vec p);
    };

};
};

#endif
