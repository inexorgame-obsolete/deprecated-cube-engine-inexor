#include "inexor/flowgraph/functions/fl_conoutf.h"

/// Inexor namespace protection
namespace inexor {
namespace vscript {

/// please note: there is no standard constructor

/// overloaded constructor
function_conoutf_node::function_conoutf_node(vec pos, const char* raw_text)
{
    position = pos;
    node_name = "Function - conoutf";
    node_comment = "Outputs a text to the local game console";
        
    /// copy raw text
    raw_text_input = raw_text;

    default_box_color = VSCRIPT_COLOR_FUNCTION;
    box_color = default_box_color;

    /// TODO: function implementation
    type = NODE_TYPE_FUNCTION;
}


function_conoutf_node::~function_conoutf_node()
{
}


void function_conoutf_node::in()
{
    /// conoutf() directly on input!
    run();
}


void function_conoutf_node::run()
{
    format_output();
    conoutf(CON_DEBUG, param_text_output.c_str());
    /// save time for color effect
    last_time = this_time;
}


/// TODO:
void function_conoutf_node::format_output()
{
    param_text_output = raw_text_input;
}


/// TODO
void function_conoutf_node::out()
{
}


/// TODO
void function_conoutf_node::reset()
{
}

/// end of namespace
};
};
