#include "inexor/engine/engine.h"
#include "inexor/flowgraph/node/fl_nodebase.h"

namespace inexor {
namespace vscript {

    CScriptNode::CScriptNode()
    {
        position = vec(0,0,0);
        type = NODE_TYPE_INVALID;
        active = true;       
        node_name = "";
        node_comment = "";        
        default_box_color = VSCRIPT_COLOR_TIMER; 
        box_color = default_box_color;
        pos_changed = false;
        selected = false;
        done_pointer = nullptr;
        script_execution_start = 0;
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
            // this is a dead end in code!
            /*if(type != NODE_TYPE_TIMER)
            {
                *done_pointer = true;
            }*/
        }
        else
        {
            /// TODO: implement return value buffer!
            for(unsigned int i=0; i<children.size(); i++)
            {
                children[i]->script_execution_start = script_execution_start;
                children[i]->in();
            }    
        }
    }

};
};
