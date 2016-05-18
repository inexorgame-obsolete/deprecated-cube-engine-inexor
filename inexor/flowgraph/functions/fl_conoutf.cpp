#include "inexor/flowgraph/functions/fl_conoutf.hpp"

namespace inexor {
namespace vscript {


    CFunctionConoutfNode::CFunctionConoutfNode(vec position, const char* raw_text)
    {
        type = NODE_TYPE_FUNCTION;
        node_name = "conoutf";
        node_comment = raw_text;
        pos = position;
        raw_text_input = raw_text;
        default_box_color = VSCRIPT_COLOR_FUNCTION;
        box_color = default_box_color;
    }

    CFunctionConoutfNode::~CFunctionConoutfNode()
    {
    }



    void CFunctionConoutfNode::in()
    {
        format_output();
        conoutf(CON_DEBUG, param_text_output.c_str());
        last_time = this_time;
    }


    void CFunctionConoutfNode::format_output()
    {
        param_text_output = raw_text_input;
    }



    bool CFunctionConoutfNode::OnLinkAsChildNodeAttempt(CScriptNode* parent)
    {
        return true;
    }
    bool CFunctionConoutfNode::OnLinkAsParentNodeAttempt(CScriptNode* child)
    {
        return false;
    }
};
};
