#include "inexor/flowgraph/comment/fl_comment.h"

namespace inexor {
namespace vscript {

    CCommentNode::CCommentNode(vec pos,
                               const char* comment, 
                               const char* name)
    {
        position = pos;
        type = NODE_TYPE_COMMENT;
        node_name = name;
        node_comment = comment;
        default_box_color = VSCRIPT_COLOR_COMMENT;
        box_color = default_box_color;
    }


    CCommentNode::~CCommentNode()
    {
    }

};
};
