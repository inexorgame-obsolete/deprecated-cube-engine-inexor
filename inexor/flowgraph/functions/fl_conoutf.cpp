#include "inexor/flowgraph/functions/fl_conoutf.hpp"

namespace inexor {
namespace vscript {

    CFunctionConoutfNode::CFunctionConoutfNode(vec position, const char* raw_text)
    {
        pos = position;
        type = NODE_TYPE_FUNCTION;
        node_name = "conoutf";
        node_comment = raw_text;
        console_text = raw_text;
        default_box_color = VSCRIPT_COLOR_FUNCTION;
        box_color = default_box_color;
    }

    CFunctionConoutfNode::~CFunctionConoutfNode()
    {
    }

    void CFunctionConoutfNode::in()
    {
        // TODO: format output (but how??)
        conoutf(CON_DEBUG, console_text.c_str());
        last_time = this_time;
    }

    bool CFunctionConoutfNode::OnLinkAsChildNodeAttempt(CScriptNode* parent)
    {
        return true;
    }

    // a function itself can not start any code at all!
    bool CFunctionConoutfNode::OnLinkAsParentNodeAttempt(CScriptNode* child)
    {
        return false;
    }
};
};
