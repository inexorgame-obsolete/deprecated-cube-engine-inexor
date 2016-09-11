#include "inexor/flowgraph/events/base/fl_event_base.hpp"

namespace inexor {
namespace vscript {

    CEventBaseNode::CEventBaseNode()
    {
    }

    CEventBaseNode::~CEventBaseNode()
    {
    }


    void CEventBaseNode::check_trigger()
    {
    }
    
    INEXOR_VSCRIPT_EVENT_TYPE CEventBaseNode::get_event_type()
    {
        return event_type;
    }
    
    bool CEventBaseNode::OnLinkAsChildNodeAttempt(CScriptNode* parent)
    {
        return false;
    }
    bool CEventBaseNode::OnLinkAsParentNodeAttempt(CScriptNode* child)
    {
        return false;
    }

};
};
