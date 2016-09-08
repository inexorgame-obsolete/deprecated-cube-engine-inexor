#include "inexor/flowgraph/areas/sphere/fl_area_sphere.hpp"

namespace inexor {
namespace vscript {

    CSphereAreaNode::CSphereAreaNode(vec position, float rad)
    {
        type = INEXOR_VSCRIPT_NODE_TYPE_AREA_SPHERE;
        pos = position;
        sphere_radius = rad;
    }

    CSphereAreaNode::~CSphereAreaNode()
    {
    }

    bool CSphereAreaNode::collide(vec p)
    {
        return true;
    }

    float CSphereAreaNode::get_radius()
    {
        return sphere_radius;
    }

    void CSphereAreaNode::render_additional()
    {
        //XY
        glBegin(GL_LINE_LOOP);
        gle::color(vec::hexcolor(INEXOR_VSCRIPT_COLOR_AREA));
        for (int i = 0; i<render_detail_level; i++)
        {
            vec p(pos);
            p.add(boxsize / 2);
            const vec2 &sc = sincos360[i*(360 / render_detail_level)];
            p[0] += sphere_radius * sc.x;
            p[1] += sphere_radius * sc.y;
            glVertex3f(p.x, p.y, p.z);
        }
        glEnd();

        // YZ
        glBegin(GL_LINE_LOOP);
        for (int i = 0; i<render_detail_level; i++)
        {
            vec p(pos);
            p.add(boxsize / 2);
            const vec2 &sc = sincos360[i*(360 / render_detail_level)];
            p[1] += sphere_radius * sc.x;
            p[2] += sphere_radius * sc.y;
            glVertex3f(p.x, p.y, p.z);
        }
        glEnd();

        //XZ
        glBegin(GL_LINE_LOOP);
        for (int i = 0; i<render_detail_level; i++)
        {
            vec p(pos);
            p.add(boxsize / 2);
            const vec2 &sc = sincos360[i*(360 / render_detail_level)];
            p[0] += sphere_radius * sc.x;
            p[2] += sphere_radius * sc.y;
            glVertex3f(p.x, p.y, p.z);
        }
        glEnd();
    }

    bool CSphereAreaNode::OnLinkAsChildNodeAttempt(CScriptNode* parent)
    {
        conoutf(CON_DEBUG, "[3DVS-boxarea] a sphere area can't run any code so it can't be linked as child!");
        return false;
    }

    bool CSphereAreaNode::OnLinkAsParentNodeAttempt(CScriptNode* child)
    {
        if(child->type != INEXOR_VSCRIPT_NODE_TYPE_EVENT)
        {
            conoutf(CON_DEBUG, "[3DVS-boxarea] a sphere can only be linked as parent of an event node!");
        }
        return true;
    }

};
};
