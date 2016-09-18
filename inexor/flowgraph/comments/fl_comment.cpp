#include "inexor/flowgraph/comments/fl_comment.hpp"

namespace inexor {
namespace vscript {

    CCommentNode::CCommentNode(vec position)
    {
        type = INEXOR_VSCRIPT_NODE_TYPE_COMMENT;
        pos = position;
        default_box_color = INEXOR_VSCRIPT_COLOR_COMMENT;
        box_color = default_box_color;
    }

    CCommentNode::~CCommentNode()
    {
    }


    bool CCommentNode::OnRelationDragStart()
    {
        spdlog::get("global")->debug() << "[3DVS-node-linker] comments can't be linked as child or parent nodes!";
        return false;
    }

    bool CCommentNode::OnLinkAsChildNodeAttempt(CScriptNode* parent)
    {
        spdlog::get("global")->debug() << "[3DVS-node-linker] comments can't be linked as child or parent nodes!";
        return false;
    }

    bool CCommentNode::OnLinkAsParentNodeAttempt(CScriptNode* child)
    {
        spdlog::get("global")->debug() << "[3DVS-node-linker] comments can't be linked as child or parent nodes!";
        return false;
    }

};
};
