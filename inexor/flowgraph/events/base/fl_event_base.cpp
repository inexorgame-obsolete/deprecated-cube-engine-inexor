#include "inexor/flowgraph/events/base/fl_event_base.hpp"

namespace inexor {
namespace vscript {

    CEventBaseNode::CEventBaseNode()
    {
    }

    CEventBaseNode::~CEventBaseNode()
    {
    }


    void CEventBaseNode::in()
    {
    }

    void CEventBaseNode::check_trigger()
    {
    }

    void CEventBaseNode::out()
    {
    }

    bool CEventBaseNode::OnLinkAsChildNodeAttempt(CScriptNode* parent)
    {
        return true;
    }
    bool CEventBaseNode::OnLinkAsParentNodeAttempt(CScriptNode* child)
    {
        // TODO: specify rules!
        return true;
    }

};
};
