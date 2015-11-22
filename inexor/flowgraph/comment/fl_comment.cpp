#include "inexor/flowgraph/comment/fl_comment.h"


namespace inexor {
namespace vscript {

    CCommentNode::CCommentNode(vec pos, const char* comment, const char* name)
    {
        type = NODE_TYPE_COMMENT;
        position = pos;
        node_comment = comment;
        node_name = name;
        default_box_color = VSCRIPT_COLOR_COMMENT;
        box_color = default_box_color;
    }


    CCommentNode::~CCommentNode()
    {
    }


/// end of namespaces
};
};
