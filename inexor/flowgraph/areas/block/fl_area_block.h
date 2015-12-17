/// @file fl_area_cube.h
/// @author Johannes Schneider
/// @brief defines cube areas

#include "inexor/flowgraph/node/fl_nodebase.h"

namespace inexor {
namespace vscript {

    class CCubeAreaNode : public CScriptNode
    {
        public:
        
            vec edge_start;
            vec edge_end;

            CCubeAreaNode(vec,vec,const char*,const char*);
            ~CCubeAreaNode();

            void reset();
            
            void render(int,bool);
            
            bool collide(vec p);
    };

};
};
