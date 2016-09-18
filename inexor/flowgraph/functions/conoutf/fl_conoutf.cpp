#include "inexor/flowgraph/functions/conoutf/fl_conoutf.hpp"

namespace inexor {
namespace vscript {

    CFunctionConoutfNode::CFunctionConoutfNode(const vec position, const char* raw_text)
    {
        pos = position;
        type = INEXOR_VSCRIPT_NODE_TYPE_FUNCTION;
        node_name = "conoutf";
        node_comment = raw_text;
        console_text = raw_text;
        default_box_color = INEXOR_VSCRIPT_COLOR_FUNCTION;
        box_color = default_box_color;
    }

    CFunctionConoutfNode::~CFunctionConoutfNode()
    {
    }


    void CFunctionConoutfNode::in()
    {
        // TODO: format output!
        spdlog::get("global")->info() << console_text.c_str();
        last_time = this_time;
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
