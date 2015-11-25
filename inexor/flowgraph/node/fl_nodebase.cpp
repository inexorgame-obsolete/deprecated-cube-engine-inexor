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
        /// Please note that nodes are invalid by default.
        /// The constructor of the child classes needs to change this.
        type = NODE_TYPE_INVALID;
        default_box_color = VSCRIPT_COLOR_TIMER; 
        box_color = default_box_color;
        active = true;       
        node_name = "";
        node_comment = "";        
        position = vec(0,0,0);
        pos_changed = false;
        selected = false;
        done_pointer = nullptr;
    }


    CScriptNode::~CScriptNode()
    {
    }


    void CScriptNode::in()
    {
        /// Calculate the time difference
        unsigned long current_time = SDL_GetTicks();
        if(current_time - *exec_time_pointer)
        {
            done_pointer = false;
            WhereDidWeStop = this;
        }
        else
        {
            run();
        }
    }


    void CScriptNode::out()
    {
        if(children.size() == 0)
        {
            /// this is a dead end in code!
            if(type != NODE_TYPE_TIMER)
            {
                *done_pointer = true;
            }
        }
        else
        {
            /// TODO: really run ALL child nodes?
            /// TODO: implement return value buffer!
            for(unsigned int i=0; i<children.size(); i++)
            {
                /// notify child nodes!
                children[i]->in();
            }    
        }
    }


/// end of namespaces
};
};
