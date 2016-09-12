#include "inexor/flowgraph/nodebase/fl_base.hpp"
#include "inexor/flowgraph/timer/fl_timer.hpp"

namespace inexor {
namespace vscript {

    CScriptNode::CScriptNode()
    {
        pos = vec(0,0,0);
        type = INEXOR_VSCRIPT_NODE_TYPE_INVALID;
        default_box_color = INEXOR_VSCRIPT_COLOR_TIMER; 
        box_color = default_box_color;
        pos_changed = false;
        selected = false;
        triggered = false;
        this_time = 0;
        last_time = 0;
        recursion_counter = 0;
        node_comment = "";
        node_name = "";
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

    void CScriptNode::set_name(const char* name)
    {
        node_name = name;
    }

    void CScriptNode::set_comment(const char* comment)
    {
        node_comment = comment;
    }

    bool CScriptNode::OnRelationDragStart()
    {
        return true;
    }

    bool CScriptNode::OnRelationDragEnd()
    {
        return true;
    }

    bool CScriptNode::OnLinkAsChildNodeAttempt(const CScriptNode* parent)
    {
        return true;
    }
    bool CScriptNode::OnUnLinkAsChildNodeAttempt(const CScriptNode* parent)
    {
        return true;
    }

    bool CScriptNode::OnLinkAsParentNodeAttempt(const CScriptNode* child)
    {
        return true;
    }
    bool CScriptNode::OnUnLinkAsParentNodeAttempt(const CScriptNode* child)
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
    }

    void CScriptNode::render(int orient, bool sel_blocked)
    {
        vec p = pos;
        render_box(p, orient);

        if(! sel_blocked)
        {
            if(orient != INEXOR_VSCRIPT_BOX_NO_INTERSECTION)
            {
                gle::color(vec::hexcolor(INEXOR_VSCRIPT_COLOR_GRAY));
                // TODO: decide about displaying help lines or not
                //render_box_helplines(p);
            }
        }
        gle::color(vec::hexcolor(INEXOR_VSCRIPT_COLOR_BLACK));
        render_box_outline(p);

        // render white text above
        p.add(vec(boxsize/2));
        p.add(vec(0,0,4));
        particle_text(p + vec(0,0,1.0f), this->node_name.c_str(), PART_TEXT, 1, 0xFFFFFF, 1.0f);
        particle_text(p, this->node_comment.c_str(), PART_TEXT, 1, 0xFFFFFF, 1.0f);

        render_additional();
    }

};
};
