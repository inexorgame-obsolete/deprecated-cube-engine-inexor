/// @file fl_area_block.h
/// @author Johannes Schneider
/// @brief 

#ifndef INEXOR_VSCRIPT_AREA_BLOCK_HEADER
#define INEXOR_VSCRIPT_AREA_BLOCK_HEADER

#include "inexor/flowgraph/nodebase/fl_base.hpp"

namespace inexor {
namespace vscript {

    class CCubeAreaNode : public CScriptNode
    {
        public:

            vec edge;

            CCubeAreaNode(vec,vec,const char*,const char*);
            ~CCubeAreaNode();
            
            bool collide(vec p);
            void render(int, bool);
    };

};
};

#endif
