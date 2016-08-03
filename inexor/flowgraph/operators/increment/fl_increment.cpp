#include "inexor/flowgraph/operators/increment/fl_increment.hpp"

namespace inexor {
namespace vscript {

    CIncrementOperator::CIncrementOperator()
    {
    }

    CIncrementOperator::~CIncrementOperator()
    {
    }

    void CIncrementOperator::in()
    {
        if(0 == children.size())
        {
            conoutf(CON_DEBUG, "[3DVS-operator-increment] no child nodes to increment");
        }

        for(unsigned int i = 0; i < children.size(); i++)
        {
            if(NODE_TYPE_MEMORY == children[i]->type)
            {
                children[i]->mem_increment_value();
            }
        }
    }
    
    bool CIncrementOperator::OnLinkAsChildNodeAttempt(CScriptNode* parent)
    {
        return true;
    }

    bool CIncrementOperator::OnLinkAsParentNodeAttempt(CScriptNode* child)
    {
        return true;
    }

};
};
