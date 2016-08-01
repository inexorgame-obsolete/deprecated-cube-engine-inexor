/// @file fl_area_block.h
/// @author Johannes Schneider
/// @brief 

#ifndef INEXOR_VSCRIPT_AREA_CONE_HEADER
#define INEXOR_VSCRIPT_AREA_CONE_HEADER

#include "inexor/flowgraph/nodebase/fl_base.hpp"


namespace inexor {
namespace vscript {

    class CConeAreaNode : public CScriptNode
    {
        protected:
            
            float cone_height;
            float cone_radius;
            const int circle_detail_level = 60;

        public:

            CConeAreaNode(vec,float,float,const char*,const char*);
            ~CConeAreaNode();
            
            bool collide(vec p);
            void render_additional();

            bool OnLinkAsChildNodeAttempt(CScriptNode* parent);
            bool OnLinkAsParentNodeAttempt(CScriptNode* child);
    };

};
};

#endif

