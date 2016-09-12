#include "inexor/flowgraph/areas/sphere/fl_area_sphere.hpp"

namespace inexor {
namespace vscript {

    CSphereAreaNode::CSphereAreaNode(const vec position, const float rad)
    {
        type = INEXOR_VSCRIPT_NODE_TYPE_AREA_SPHERE;
        pos = position;
        sphere_radius = rad;
    }

    CSphereAreaNode::~CSphereAreaNode()
    {
    }


    float CSphereAreaNode::get_radius()
    {
        return sphere_radius;
    }

    bool CSphereAreaNode::is_point_inside_sphere(const vec point_pos)
    {
        // TODO: speed this up by using the squared method (see David Scherfgen's book)
        return pos.dist(point_pos) < sphere_radius;
    }

    void CSphereAreaNode::render_additional()
    {
        //XY
        glBegin(GL_LINE_LOOP);
        gle::color(vec::hexcolor(INEXOR_VSCRIPT_COLOR_AREA));
        if(is_point_inside_sphere(game::player1->o)) gle::color(vec::hexcolor(INEXOR_VSCRIPT_COLOR_TRIGGERED));
        
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

    bool CSphereAreaNode::OnLinkAsChildNodeAttempt(const CScriptNode* parent)
    {
        conoutf(CON_DEBUG, "[3DVS-area-sphere] a sphere area can't run any code so it can't be linked as child node!");
        return false;
    }

    bool CSphereAreaNode::OnLinkAsParentNodeAttempt(const CScriptNode* child)
    {
        if(INEXOR_VSCRIPT_NODE_TYPE_EVENT != child->type)
        {
            conoutf(CON_DEBUG, "[3DVS-area-sphere] a sphere can only be linked as parent of an event node!");
            return false;
        }
        return true;
    }

};
};
