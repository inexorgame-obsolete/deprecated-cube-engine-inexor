#include "inexor/flowgraph/functions/fl_conoutf.h"


namespace inexor {
namespace vscript {

    CFunctionConoutfNode::CFunctionConoutfNode(vec pos, const char* raw_text)
    {
        position = pos;
        node_name = "Function - conoutf";
        node_comment = "Outputs a text to the local game console";
        
        /// copy raw text
        raw_text_input = raw_text;

        default_box_color = VSCRIPT_COLOR_FUNCTION;
        box_color = default_box_color;
        type = NODE_TYPE_FUNCTION;
    }


    CFunctionConoutfNode::~CFunctionConoutfNode()
    {
    }


    void CFunctionConoutfNode::in()
    {
        /// call conoutf() directly on input!
        run();
    }


    void CFunctionConoutfNode::run()
    {
        format_output();
        conoutf(CON_DEBUG, param_text_output.c_str());
        /// save time for color effect
        last_time = this_time;
    }


    /// TODO:
    void CFunctionConoutfNode::format_output()
    {
        param_text_output = raw_text_input;
    }


    /// TODO
    void CFunctionConoutfNode::out()
    {
        for(unsigned int i = 0; i < outgoing.size(); i++) outgoing[i]->in();
    }


    /// TODO
    void CFunctionConoutfNode::reset()
    {
    }


/// end of namespaces
};
};
