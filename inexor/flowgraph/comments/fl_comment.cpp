#include "inexor/flowgraph/comments/fl_comment.hpp"

namespace inexor {
namespace vscript {

    CCommentNode::CCommentNode(vec position,
                               const char* comment, 
                               const char* name)
    {
        pos = position;
        type = INEXOR_VSCRIPT_NODE_TYPE_COMMENT;
        node_name = name;
        node_comment = comment;
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

    bool CCommentNode::OnLinkAsChildNodeAttempt(CScriptNode* parent)
    {
        conoutf(CON_DEBUG, "[3DVS-node-linker] comments can't be linked as child or parent nodes!");
        return false;
    }

    bool CCommentNode::OnLinkAsParentNodeAttempt(CScriptNode* child)
    {
        conoutf(CON_DEBUG, "[3DVS-node-linker] comments can't be linked as child or parent nodes!");
        return false;
    }

};
};
