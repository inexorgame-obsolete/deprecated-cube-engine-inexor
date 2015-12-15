#include "inexor/engine/engine.h"
#include "inexor/flowgraph/node/fl_nodebase.h"

namespace inexor {
namespace vscript {


    CScriptNode::CScriptNode()
    {
        pos = vec(0,0,0);
        type = NODE_TYPE_INVALID;
        node_name = "";
        node_comment = "";
        default_box_color = VSCRIPT_COLOR_TIMER; 
        box_color = default_box_color;
        pos_changed = false;
        selected = false;
    }


    CScriptNode::~CScriptNode()
    {
    }


    void CScriptNode::in()
    {
        run();
    }


    void CScriptNode::out()
    {
        if(children.size() == 0)
        {
            /// TODO: end thread(?)
        }
        else
        {
            for(unsigned int i=0; i<children.size(); i++)
            {
                children[i]->in();
            }
        }
    }

};
};
