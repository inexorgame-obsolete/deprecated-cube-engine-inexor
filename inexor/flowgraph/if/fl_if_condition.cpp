#include "inexor/flowgraph/if/fl_if_condition.hpp"

namespace inexor {
namespace vscript {

    CIfNode::CIfNode(vec position)
    {
        type = INEXOR_VSCRIPT_NODE_TYPE_IF;
        pos = position;
    }

    CIfNode::~CIfNode()
    {
    }


    void CIfNode::in()
    {
        // TODO
    }

    void CIfNode::render_additional(vec p)
    {
        particle_text(p + vec(0.0f, 0.0f, -(2.0f+boxsize) ), "attributes here! :)", PART_TEXT, 1, 0xFFFFFF, 1.0f);
    }

    bool CIfNode::OnLinkAsChildNodeAttempt(CScriptNode* parent)
    {
        return false;
    }

    bool CIfNode::OnLinkAsParentNodeAttempt(CScriptNode* child)
    {
        return true;
    }


};
};
