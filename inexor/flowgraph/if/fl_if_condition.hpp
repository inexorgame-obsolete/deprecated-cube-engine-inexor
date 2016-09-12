/// @file fl_if_condition.hpp
/// @author Johannes Schneider
/// @brief implements boolean values.

#ifndef INEXOR_VSCRIPT_IF_CONDITION_HEADER
#define INEXOR_VSCRIPT_IF_CONDITION_HEADER

#include "inexor/flowgraph/nodebase/fl_base.hpp"
#include "inexor/flowgraph/memory/bool/fl_mem_bool.hpp"


namespace inexor {
namespace vscript {

    class CIfNode : public CScriptNode
    {
        public:
        
            CIfNode(const vec);
            ~CIfNode();

            // the condition to check
            CMemBoolNode *statement;

            CScriptNode* condition_true_node;
            CScriptNode* condition_false_node;

            void in();
            void check_condition();
            void condition_true_out();
            void condition_false_out();

            void render_additional(const vec p);

            bool OnLinkAsChildNodeAttempt(CScriptNode*);
            bool OnLinkAsParentNodeAttempt(CScriptNode*);
    };

};
};

#endif
