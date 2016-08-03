/// @file fl_increment.hpp
/// @author Johannes Schneider
/// @brief increments a variable

#ifndef INEXOR_VSCRIPT_INCREMENT_HEADER
#define INEXOR_VSCRIPT_INCREMENT_HEADER

#include "inexor/flowgraph/nodebase/fl_base.hpp"

namespace inexor {
    namespace vscript {

        class CIncrementOperator : public CScriptNode
        {
        public:

            CIncrementOperator();
            ~CIncrementOperator();

            void in();

            bool OnLinkAsChildNodeAttempt(CScriptNode* parent);
            bool OnLinkAsParentNodeAttempt(CScriptNode* child);
        };

    };
};

#endif
