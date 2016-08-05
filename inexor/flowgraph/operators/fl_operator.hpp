/// @file fl_operator.hpp
/// @author Johannes Schneider
/// @brief increments a variable

#ifndef INEXOR_VSCRIPT_OPERATOR_HEADER
#define INEXOR_VSCRIPT_OPERATOR_HEADER

#include "inexor/flowgraph/nodebase/fl_base.hpp"
#include "inexor/flowgraph/memory/integer/fl_mem_integer.hpp"
#include "inexor/flowgraph/memory/float/fl_mem_float.hpp"

namespace inexor {
namespace vscript {

    class COperatorNode : public CScriptNode
    {
        public:

            COperatorNode(vec, INEXOR_VSCRIPT_OPERATOR_TYPE, const char*, const char*);
            ~COperatorNode();

            void in();

            bool OnLinkAsChildNodeAttempt(CScriptNode* parent);
            bool OnLinkAsParentNodeAttempt(CScriptNode* child);

        protected:

            INEXOR_VSCRIPT_OPERATOR_TYPE operator_type;

            // TODO: overload these methods?
            void apply_operator_on_integer(CMemIntegerNode*);
            void apply_operator_on_float(CMemFloatNode*);
    };

};
};

#endif
