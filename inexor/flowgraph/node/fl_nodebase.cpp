#include "inexor/engine/engine.h"

#include <string>
#include <vector>
#include <map>
#include <list>

#include "inexor/flowgraph/node/fl_nodebase.h"


namespace inexor {
namespace vscript {

    CScriptNode::CScriptNode()
    {
        active = true;       
        node_name = "";
        node_comment = "";        
        position = vec(0,0,0);
        pos_changed = false;
        selected = false;
        default_box_color = VSCRIPT_COLOR_TIMER; 
        box_color = default_box_color;

        /// Please note that nodes are invalid by default.
        /// The constructor of the child classes needs to change this.
        type = NODE_TYPE_INVALID;
    }


    CScriptNode::~CScriptNode()
    {
    }


/// end of namespaces
};
};
