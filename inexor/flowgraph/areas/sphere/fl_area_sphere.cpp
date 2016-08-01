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
        gle::color(vec::hexcolor(VSCRIPT_AREA));

        gle::begin(GL_LINE_LOOP);
        for (int i = 0; i<circle_detail_level; i++)
        {
            vec p(pos);
            p.add(boxsize / 2);
            const vec2 &sc = sincos360[i*(360 / circle_detail_level)];
            p[0] += radius * sc.x;
            p[1] += radius * sc.y;

            glVertex3f(p.x, p.y, p.z);
        }
        gle::end();

        gle::begin(GL_LINE_LOOP);
        for (int i = 0; i<circle_detail_level; i++)
        {
            vec p(pos);
            p.add(boxsize / 2);
            const vec2 &sc = sincos360[i*(360 / circle_detail_level)];
            p[1] += radius * sc.x;
            p[2] += radius * sc.y;

            glVertex3f(p.x, p.y, p.z);
        }
        gle::end();

        gle::begin(GL_LINE_LOOP);
        for (int i = 0; i<circle_detail_level; i++)
        {
            vec p(pos);
            p.add(boxsize / 2);
            const vec2 &sc = sincos360[i*(360 / circle_detail_level)];
            p[0] += radius * sc.x;
            p[2] += radius * sc.y;

            glVertex3f(p.x, p.y, p.z);
        }
        gle::end();
    }

    bool CSphereAreaNode::OnLinkAsChildNodeAttempt(CScriptNode* parent)
    {
        conoutf(CON_DEBUG, "[box-area] a sphere area can't run any code so it can't be linked as child!");
        return false;
    }

    bool CSphereAreaNode::OnLinkAsParentNodeAttempt(CScriptNode* child)
    {
        if(child->type != NODE_TYPE_EVENT)
        {
            conoutf(CON_DEBUG, "[box-area] a sphere can only be linked as parent of an event node!");
        }
        return true;
    }

};
};
