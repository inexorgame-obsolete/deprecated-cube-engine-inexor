#include "inexor/flowgraph/nodebase/fl_base.hpp"
#include "inexor/flowgraph/timer/fl_timer.hpp"

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
        triggered = false;
        this_time = 0;
        last_time = 0;
        recursion_counter = 0;
    }
    
    CScriptNode::~CScriptNode()
    {
    }

    SNodeRelation::SNodeRelation()
    {
    }

    SNodeRelation::~SNodeRelation()
    {
    }

    bool CScriptNode::OnRelationDragStart()
    {
        conoutf(CON_DEBUG, "[3DVS-nodes] dragging started.");
        return true;
    }

    bool CScriptNode::OnRelationDragEnd()
    {
        conoutf(CON_DEBUG, "[3DVS-nodes] dragging stopped.");
        return true;
    }

    // The editor is trying to link/unlink it as child of another node
    bool CScriptNode::OnLinkAsChildNodeAttempt(CScriptNode* parent)
    {
        return true;
    }
    bool CScriptNode::OnUnLinkAsChildNodeAttempt(CScriptNode* parent)
    {
        return true;
    }

    // The editor is trying to link/unlink it as parent of another node
    bool CScriptNode::OnLinkAsParentNodeAttempt(CScriptNode* child)
    {
        return true;
    }
    bool CScriptNode::OnUnLinkAsParentNodeAttempt(CScriptNode* child)
    {
        return true;
    }

    void CScriptNode::in()
    {
    }

    void CScriptNode::reset()
    {
    }

    void CScriptNode::out()
    {
        if(children.size() == 0)
        {
        }
        else
        {
            for(unsigned int i=0; i<children.size(); i++)
            {
                children[i]->in();
            }
        }
    }

    void CScriptNode::render_additional()
    {
        // TODO: implement additional render stuff depending on the node type
    }

    void CScriptNode::render(int orient, bool sel_blocked)
    {
        vec p = pos;
        render_box(p, orient);

        if(! sel_blocked)
        {
            if(orient != VSCRIPT_BOX_NO_INTERSECTION)
            {
                gle::color(vec::hexcolor(VSCRIPT_COLOR_GRAY));
                // TODO: decide about displaying help lines or not
                //render_box_helplines(p);
            }
        }
        gle::color(vec::hexcolor(VSCRIPT_COLOR_BLACK));
        render_box_outline(p);

        // render white text above
        p.add(vec(boxsize/2));
        p.add(vec(0,0,4));
        particle_text(p + vec(0,0,1.0f), this->node_name.c_str(), PART_TEXT, 1, 0xFFFFFF, 1.0f);
        particle_text(p, this->node_comment.c_str(), PART_TEXT, 1, 0xFFFFFF, 1.0f);

        // some nodes require additional rendering stuff
        render_additional();
    }

};
};
