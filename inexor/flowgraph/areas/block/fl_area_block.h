/// @file fl_area_cube.h
/// @author Johannes Schneider
/// @brief defines cube areas

#include "inexor/flowgraph/nodebase/fl_base.h"

namespace inexor {
namespace vscript {

    class CCubeAreaNode : public CScriptNode
    {
        public:

            vec edge;

            CCubeAreaNode(vec,vec,const char*,const char*);
            ~CCubeAreaNode();

            void reset();

            void render(int,bool);

            void in() {}

            bool collide(vec p);
    };

};
};
