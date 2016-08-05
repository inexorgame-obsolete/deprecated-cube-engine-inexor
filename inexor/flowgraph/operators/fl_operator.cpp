#include "inexor/flowgraph/operators/fl_operator.hpp"

namespace inexor {
namespace vscript {

    COperatorNode::COperatorNode(vec position, INEXOR_VSCRIPT_OPERATOR_TYPE op_type)
    {
        type = INEXOR_VSCRIPT_NODE_TYPE_OPERATOR;
        operator_type = op_type;
        pos = position;
        default_box_color = INEXOR_VSCRIPT_COLOR_OPERATOR;
        box_color = default_box_color;
    }

    COperatorNode::~COperatorNode()
    {
    }

    void COperatorNode::apply_operator_on_integer(CMemIntegerNode* node)
    {
        switch(operator_type)
        {
            case INEXOR_VSCRIPT_OPERATOR_TYPE_INCREMENT:
            {
                node->increment();
                break;
            }
            case INEXOR_VSCRIPT_OPERATOR_TYPE_DECREMENT:
            {
                node->decrement();
                break;
            }
            case INEXOR_VSCRIPT_OPERATOR_TYPE_SETNULL:
            {
                node->set_value(0);
                break;
            }
        }
    }

    void COperatorNode::apply_operator_on_float(CMemFloatNode* node)
    {
        switch(operator_type)
        {
            case INEXOR_VSCRIPT_OPERATOR_TYPE_INCREMENT:
            {
                node->increment();
                break;
            }
            case INEXOR_VSCRIPT_OPERATOR_TYPE_DECREMENT:
            {
                node->decrement();
                break;
            }
            case INEXOR_VSCRIPT_OPERATOR_TYPE_SETNULL:
            {
                node->set_value(0.0);
                break;
            }
        }
    }

    void COperatorNode::in()
    {
        last_time = this_time;
        if(0 == children.size())
        {
            conoutf(CON_DEBUG, "[3DVS-operator-increment] no child nodes to increment");
        }

        for(unsigned int i = 0; i < children.size(); i++)
        {
            switch(children[i]->type)
            {
                case INEXOR_VSCRIPT_NODE_TYPE_MEMORY_INTEGER:
                {
                    apply_operator_on_integer(static_cast<CMemIntegerNode*>(children[i]));
                    break;
                }
                case INEXOR_VSCRIPT_NODE_TYPE_MEMORY_FLOAT:
                {
                    apply_operator_on_float(static_cast<CMemFloatNode*>(children[i]));
                    break;
                }
            }
        }
    }
    
    bool COperatorNode::OnLinkAsChildNodeAttempt(CScriptNode* parent)
    {
        switch(parent->type)
        {
            case INEXOR_VSCRIPT_NODE_TYPE_SLEEP:
            case INEXOR_VSCRIPT_NODE_TYPE_TIMER:
                return true;
        }
        return false;
    }

    bool COperatorNode::OnLinkAsParentNodeAttempt(CScriptNode* child)
    {
        switch(child->type)
        {
            case INEXOR_VSCRIPT_NODE_TYPE_MEMORY_INTEGER:
            case INEXOR_VSCRIPT_NODE_TYPE_MEMORY_FLOAT:
                return true;
                break;
        }
        return false;
    }

};
};
