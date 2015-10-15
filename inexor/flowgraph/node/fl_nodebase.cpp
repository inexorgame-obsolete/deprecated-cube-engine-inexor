#include "inexor/flowgraph/node/fl_nodebase.h"

/// Inexor namespace protection
namespace inexor {
namespace vscript {

script_node::script_node()
{
    /// Please note that nodes are invalid by default.
    active = true;       
    node_name = "";
    node_comment = "";        
    position = vec(0,0,0);
    pos_changed = false;
    selected = false;
    default_box_color = VSCRIPT_COLOR_TIMER; 
    box_color = default_box_color;

    /// the constructor of the child classes needs to change this.
    type = NODE_TYPE_INVALID;
}


script_node::~script_node()
{
}

/// end of namespace
};
};
