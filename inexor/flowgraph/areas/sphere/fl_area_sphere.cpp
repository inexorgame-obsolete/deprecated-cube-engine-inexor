#include "inexor/flowgraph/areas/sphere/fl_area_sphere.hpp"

namespace inexor {
namespace vscript {

    CSphereAreaNode::CSphereAreaNode(vec position, float rad, const char* name, const char* comment)
    {
        type = NODE_TYPE_AREA_SPHERE;
        pos = position;
        node_name = name;
        node_comment = comment;
        radius = rad;
    }

    CSphereAreaNode::~CSphereAreaNode()
    {
    }

    bool CSphereAreaNode::collide(vec p)
    {
        return true;
    }

    void CSphereAreaNode::render_additional()
    {
        //XY
        glBegin(GL_LINE_LOOP);
        gle::color(vec::hexcolor(VSCRIPT_AREA));
        for (int i = 0; i<render_detail_level; i++)
        {
            vec p(pos);
            p.add(boxsize / 2);
            const vec2 &sc = sincos360[i*(360 / render_detail_level)];
            p[0] += radius * sc.x;
            p[1] += radius * sc.y;
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
            p[1] += radius * sc.x;
            p[2] += radius * sc.y;
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
            p[0] += radius * sc.x;
            p[2] += radius * sc.y;
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
        if(child->type != NODE_TYPE_EVENT)
        {
            conoutf(CON_DEBUG, "[3DVS-boxarea] a sphere can only be linked as parent of an event node!");
        }
        return true;
    }

};
};
