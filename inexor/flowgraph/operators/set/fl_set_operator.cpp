#include "inexor/flowgraph/operators/set/fl_set_operator.hpp"

namespace inexor {
namespace vscript {

    CSetOperatorNode::CSetOperatorNode(const vec position, const INEXOR_VSCRIPT_OPERATOR_TYPE op_type, const float assign_value) : COperatorNode(position,op_type)
    {
        value_to_assign = assign_value;
    }

    CSetOperatorNode::~CSetOperatorNode()
    {
    }


    void CSetOperatorNode::set_value(const float val)
    {
        value_to_assign = val;
    }

};
};
