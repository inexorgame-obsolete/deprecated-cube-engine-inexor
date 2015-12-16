/// @file fl_area_cube.h
/// @author Johannes Schneider
/// @brief defines cube areas

#include "inexor/flowgraph/node/fl_nodebase.h"

namespace inexor {
namespace vscript {

    class CCubeArea : public CScriptNode
    {
        public:
        
            vec edge_start;
            vec edge_end;

            CCubeArea();
            ~CCubeArea();

            bool collide(vec p);
    };

};
};
