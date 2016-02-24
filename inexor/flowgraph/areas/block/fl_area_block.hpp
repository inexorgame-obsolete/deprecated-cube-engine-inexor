/// @file fl_area_block.h
/// @author Johannes Schneider
/// @brief 

#include "inexor/flowgraph/nodebase/fl_base.hpp"

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
