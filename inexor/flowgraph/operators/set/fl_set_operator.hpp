/// @file fl_set_operator.hpp
/// @author Johannes Schneider
/// @brief The set operator requires a parameter (the set value). It is not a basic operator like setnull.

#ifndef INEXOR_VSCRIPT_SET_OPERATOR_HEADER
#define INEXOR_VSCRIPT_SET_OPERATOR_HEADER

#include "inexor/flowgraph/operators/fl_operator.hpp"

namespace inexor {
namespace vscript {

    class CSetOperatorNode : public COperatorNode
    {
        public:

            CSetOperatorNode(const vec, const INEXOR_VSCRIPT_OPERATOR_TYPE, const float);
            ~CSetOperatorNode();

            void set_value(const float);

        private:

            float value_to_assign = 0.0f;

    };

};
};

#endif
