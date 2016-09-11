#include "inexor/flowgraph/areas/cone/fl_area_cone.hpp"

namespace inexor {
namespace vscript {

    CConeAreaNode::CConeAreaNode(vec position, float radius, float height)
    {
        type = INEXOR_VSCRIPT_NODE_TYPE_AREA_BOX;
        pos = position;
        cone_height = height;
        cone_radius = radius;
    }

    CConeAreaNode::~CConeAreaNode()
    {
    }


    void CConeAreaNode::render_additional()
    {
        // 2 loops in XY plane
        glBegin(GL_LINE_LOOP);
        gle::color(vec::hexcolor(INEXOR_VSCRIPT_COLOR_AREA));
        for(int i = 0; i<render_detail_level; i++)
        {
            vec p(pos);
            p.add(boxsize / 2);
            const vec2 &sc = sincos360[i*(360 / render_detail_level)];
            p[0] += cone_radius * sc.x;
            p[1] += cone_radius * sc.y;
            glVertex3f(p.x, p.y, p.z);
        }
        glEnd();

        glBegin(GL_LINES);
        gle::color(vec::hexcolor(INEXOR_VSCRIPT_COLOR_AREA));
        for(int i = 0; i<render_detail_level; i++)
        {
            vec p(pos);
            p.add(boxsize / 2);
            const vec2 &sc = sincos360[i*(360 / render_detail_level)];
            p[0] += cone_radius * sc.x;
            p[1] += cone_radius * sc.y;
            glVertex3f(p.x, p.y, p.z);
            glVertex3f(pos.x, pos.y, pos.z + cone_height);
        }
        glEnd();

        // TODO: render connection lines!
    }

    bool CConeAreaNode::OnLinkAsChildNodeAttempt(CScriptNode* parent)
    {
        conoutf(CON_DEBUG, "[3DVS-area-cone] a cone area can't run any code so it can't be linked as child node!");
        return false;
    }

    bool CConeAreaNode::OnLinkAsParentNodeAttempt(CScriptNode* child)
    {
        if(INEXOR_VSCRIPT_NODE_TYPE_EVENT != child->type)
        {
            conoutf(CON_DEBUG, "[3DVS-area-cone] a cone can only be linked as parent of an event node!");
        }
        return true;
    }

};
};
