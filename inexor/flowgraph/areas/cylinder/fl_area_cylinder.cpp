#include "inexor/flowgraph/areas/cylinder/fl_area_cylinder.hpp"

namespace inexor {
namespace vscript {

    CCylinderAreaNode::CCylinderAreaNode(const vec position, const float radius, const float height)
    {
        type = INEXOR_VSCRIPT_NODE_TYPE_AREA_CYLINDER;
        pos = position;
        cylinder_height = height;
        cylinder_radius = radius;
    }

    CCylinderAreaNode::~CCylinderAreaNode()
    {
    }


    void CCylinderAreaNode::render_additional()
    {
        // 2 loops in XY plane
        glBegin(GL_LINE_LOOP);
        gle::color(vec::hexcolor(INEXOR_VSCRIPT_COLOR_AREA));
        for(int i = 0; i<render_detail_level; i++)
        {
            vec p(pos);
            p.add(boxsize / 2);
            const vec2 &sc = sincos360[i*(360 / render_detail_level)];
            p[0] += cylinder_radius * sc.x;
            p[1] += cylinder_radius * sc.y;
            p[2] += cylinder_height;
            glVertex3f(p.x, p.y, p.z);
        }
        glEnd();

        glBegin(GL_LINE_LOOP);
        for(int i = 0; i<render_detail_level; i++)
        {
            vec p(pos);
            p.add(boxsize / 2);
            const vec2 &sc = sincos360[i*(360 / render_detail_level)];
            p[0] += cylinder_radius * sc.x;
            p[1] += cylinder_radius * sc.y;
            p[2] -= cylinder_height;
            glVertex3f(p.x, p.y, p.z);
        }
        glEnd();

        // vertical lines
        glBegin(GL_LINES);
        for(int i = 0; i<render_detail_level; i++)
        {
            vec p(pos);
            p.add(boxsize / 2);
            const vec2 &sc = sincos360[i*(360 / render_detail_level)];
            p[0] += cylinder_radius * sc.x;
            p[1] += cylinder_radius * sc.y;
            p[2] += cylinder_height;
            glVertex3f(p.x, p.y, p.z);
            p[2] -= 2*cylinder_height;
            glVertex3f(p.x, p.y, p.z);
        }
        glEnd();
    }

    bool CCylinderAreaNode::OnLinkAsChildNodeAttempt(CScriptNode* parent)
    {
        conoutf(CON_DEBUG, "[3DVS-area-cylinder] a cone area can't run any code so it can't be linked as child node!");
        return false;
    }

    bool CCylinderAreaNode::OnLinkAsParentNodeAttempt(CScriptNode* child)
    {
        if(INEXOR_VSCRIPT_NODE_TYPE_EVENT != child->type)
        {
            conoutf(CON_DEBUG, "[3DVS-area-cylinder] a cone can only be linked as parent of an event node!");
        }
        return true;
    }

};
};
