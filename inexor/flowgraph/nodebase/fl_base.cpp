#include "inexor/flowgraph/nodebase/fl_base.h"
#include "inexor/flowgraph/timer/fl_timer.h"


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


    void CScriptNode::render(int orient, bool sel_blocked)
    {
        // hightlight node during execution
        if(SDL_GetTicks() - last_time < INEXOR_VSCRIPT_ACTIVE_NODE_TIMER_INTERVAL) box_color = VSCRIPT_COLOR_TRIGGERED;
        else box_color = default_box_color;

        vec p = this->pos;
        render_box(p, orient);

        if(!sel_blocked)
        {
            if(orient != VSCRIPT_BOX_NO_INTERSECTION)
            {
                gle::color(vec::hexcolor(VSCRIPT_COLOR_GRAY));
                render_box_helplines(p);
            }
        }
        gle::color(vec::hexcolor(VSCRIPT_COLOR_BLACK));
        render_box_outline(p);

        // render white text above
        p.add(vec(boxsize/2));
        p.add(vec(0,0,4));
        particle_text(p + vec(0,0,1.0f), this->node_name.c_str(), PART_TEXT, 1, 0xFFFFFF, 1.0f);
        particle_text(p, this->node_comment.c_str(), PART_TEXT, 1, 0xFFFFFF, 1.0f);
    }

};
};
