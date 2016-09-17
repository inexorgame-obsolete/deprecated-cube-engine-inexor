#include "inexor/flowgraph/memory/fl_membase.hpp"

namespace inexor {
namespace vscript {

    CMemoryNode::CMemoryNode()
    {
    }

    CMemoryNode::~CMemoryNode()
    {
    }


    bool CMemoryNode::OnLinkAsChildNodeAttempt(CScriptNode* parent)
    {
        switch(parent->type)
        {
            case INEXOR_VSCRIPT_NODE_TYPE_OPERATOR:
            {
                return true;
                break;
            }
        }
        return false;
    }

    bool CMemoryNode::OnLinkAsParentNodeAttempt(CScriptNode* child)
    {
        switch(child->type)
        {
            case INEXOR_VSCRIPT_NODE_TYPE_IF:
            {
                return true;
                break;
            }
        }
        return false;
    }

};
};
