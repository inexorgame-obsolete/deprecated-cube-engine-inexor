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
        conoutf(CON_DEBUG, "[3DVS-node-linker] comments can't be linked as child or parent nodes!");
        return false;
    }

    bool CCommentNode::OnLinkAsChildNodeAttempt(const CScriptNode* parent)
    {
        conoutf(CON_DEBUG, "[3DVS-node-linker] comments can't be linked as child or parent nodes!");
        return false;
    }

    bool CCommentNode::OnLinkAsParentNodeAttempt(const CScriptNode* child)
    {
        conoutf(CON_DEBUG, "[3DVS-node-linker] comments can't be linked as child or parent nodes!");
        return false;
    }

};
};
