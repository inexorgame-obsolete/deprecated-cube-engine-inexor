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

    // We could create another base class
    // which implements increment/decrement... for all
    // memory blocks, but it would have to be differenz
    // base class for e.g. boolean expressions because
    // those operators do not apply on these data types!

    void COperatorNode::increment(CScriptNode* node)
    {
        switch (node->type)
        {
            case INEXOR_VSCRIPT_NODE_TYPE_MEMORY_INTEGER:
                static_cast<CMemIntegerNode*>(node)->increment();
                break;
            case INEXOR_VSCRIPT_NODE_TYPE_MEMORY_FLOAT:
                static_cast<CMemFloatNode*>(node)->increment();
                break;
        }
    }

    void COperatorNode::decrement(CScriptNode* node)
    {
        switch (node->type)
        {
            case INEXOR_VSCRIPT_NODE_TYPE_MEMORY_INTEGER:
                static_cast<CMemIntegerNode*>(node)->decrement();
                break;
            case INEXOR_VSCRIPT_NODE_TYPE_MEMORY_FLOAT:
                static_cast<CMemFloatNode*>(node)->decrement();
                break;
        }
    }

    void COperatorNode::setnull(CScriptNode* node)
    {
        switch (node->type)
        {
            case INEXOR_VSCRIPT_NODE_TYPE_MEMORY_INTEGER:
                static_cast<CMemIntegerNode*>(node)->set_value(0);
                break;
            case INEXOR_VSCRIPT_NODE_TYPE_MEMORY_FLOAT:
                static_cast<CMemFloatNode*>(node)->set_value(0.0f);
                break;
        }
    }

    void COperatorNode::apply_operator(CScriptNode* node)
    {
        switch(operator_type)
        {
            case INEXOR_VSCRIPT_OPERATOR_TYPE_INCREMENT:
            {
                increment(node);
                break;
            }
            case INEXOR_VSCRIPT_OPERATOR_TYPE_DECREMENT:
            {
                decrement(node);
                break;
            }
            case INEXOR_VSCRIPT_OPERATOR_TYPE_SETNULL:
            {
                setnull(node);
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

        // TODO: declare code execution priority strategy!
        for(unsigned int i = 0; i < children.size(); i++)
        {
            apply_operator(children[i]);
        }
    }
    
    bool COperatorNode::OnLinkAsChildNodeAttempt(CScriptNode* parent)
    {
        switch(parent->type)
        {
            case INEXOR_VSCRIPT_NODE_TYPE_SLEEP:
            case INEXOR_VSCRIPT_NODE_TYPE_TIMER:
                return true;
                break;
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
