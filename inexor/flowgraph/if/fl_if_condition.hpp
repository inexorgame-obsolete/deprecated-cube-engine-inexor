/// @file fl_if_condition.hpp
/// @author Johannes Schneider
/// @brief implements boolean values.

#ifndef INEXOR_VSCRIPT_IF_CONDITION_HEADER
#define INEXOR_VSCRIPT_IF_CONDITION_HEADER

#include "inexor/flowgraph/nodebase/fl_base.hpp"

namespace inexor {
namespace vscript {

    class CIfNode : public CScriptNode
    {
        public:
        
            CIfNode(vec);
            ~CIfNode();
            
            // TODO ?
            void in();

            void render_additional(vec p);

            bool OnLinkAsChildNodeAttempt(CScriptNode*);
            bool OnLinkAsParentNodeAttempt(CScriptNode*);
    };

};
};

#endif
