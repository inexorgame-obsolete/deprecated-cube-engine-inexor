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

    /// @brief every operator node will be specified
    /// as one of the following operators.
    enum INEXOR_VSCRIPT_OPERATOR_TYPE
    {
        INEXOR_VSCRIPT_OPERATOR_TYPE_INCREMENT = 0,
        INEXOR_VSCRIPT_OPERATOR_TYPE_DECREMENT,
        INEXOR_VSCRIPT_OPERATOR_TYPE_SETNULL,
        INEXOR_VSCRIPT_OPERATOR_TYPE_SETVAL,
    };

    class COperatorNode : public CScriptNode
    {
        public:

            COperatorNode(const vec, const INEXOR_VSCRIPT_OPERATOR_TYPE);
            ~COperatorNode();

            void in();

            bool OnLinkAsChildNodeAttempt(CScriptNode*);
            bool OnLinkAsParentNodeAttempt(CScriptNode*);

        protected:

            INEXOR_VSCRIPT_OPERATOR_TYPE operator_type;
            void apply_operator(CScriptNode*);

        private:

            void increment(CScriptNode* node);
            void decrement(CScriptNode* node);
            void setnull(CScriptNode* node);

            // TODO: implement more operators
    };

};
};

#endif
