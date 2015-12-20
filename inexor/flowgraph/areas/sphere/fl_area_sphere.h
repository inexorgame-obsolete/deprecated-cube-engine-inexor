/// @file fl_area_sphere.h
/// @author Johannes Schneider
/// @brief defines sphere areas

#include "inexor/flowgraph/node/fl_nodebase.h"

namespace inexor {
namespace vscript {

    class CSphereAreaNode : public CScriptNode
    {
        public:

            // the distance from this vector to the position defines the radius of the sphere
            vec radius;

            CSphereAreaNode(vec,vec,const char*,const char*);
            ~CSphereAreaNode();

            void reset();

            void render(int,bool);

            bool collide(vec p);
    };

};
};
