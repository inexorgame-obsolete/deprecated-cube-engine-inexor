#include "inexor/flowgraph/areas/cone/fl_area_cone.hpp"

namespace inexor {
namespace vscript {

    CConeAreaNode::CConeAreaNode(vec position, float radius, float height, const char* name, const char* comment = "")
    {
        type = NODE_TYPE_AREA_BOX;
        pos = position;
        node_name = name;
        node_comment = comment;

        cone_height = height;
        cone_radius = radius;
    }

    CConeAreaNode::~CConeAreaNode()
    {
    }

    bool CConeAreaNode::collide(vec p)
    {
        return true;
    }

    void CConeAreaNode::render_additional()
    {
        gle::color(vec::hexcolor(VSCRIPT_AREA));
        gle::begin(GL_LINE_LOOP);
        
        for (int i = 0; i<circle_detail_level; i++)
        {
            vec p(pos);
            p.add(boxsize / 2);
            const vec2 &sc = sincos360[i*(360 / circle_detail_level)];
            p[0] += cone_radius * sc.x;
            p[1] += cone_radius * sc.y;

            glVertex3f(p.x, p.y, p.z);
        }
        gle::end();

        gle::begin(GL_LINE_LOOP);
        for (int i = 0; i<circle_detail_level; i++)
        {
            vec p(pos);
            p.add(boxsize / 2);
            const vec2 &sc = sincos360[i*(360 / circle_detail_level)];
            p[0] += cone_radius * sc.x;
            p[1] += cone_radius * sc.y;
            p[2] += cone_height;
            glVertex3f(p.x, p.y, p.z);
        }
        gle::end();

        // connection lines
        gle::begin(GL_LINES);
        for (int i = 0; i<circle_detail_level; i++)
        {
            vec p(pos);
            p.add(boxsize / 2);
            const vec2 &sc = sincos360[i*(360 / circle_detail_level)];
            p[0] += cone_radius * sc.x;
            p[1] += cone_radius * sc.y;
            glVertex3f(p.x, p.y, p.z);

            p[2] += cone_height;
            glVertex3f(p.x, p.y, p.z);
        }
        gle::end();

    }

    bool CConeAreaNode::OnLinkAsChildNodeAttempt(CScriptNode* parent)
    {
        conoutf(CON_DEBUG, "[box-area] a cone area can't run any code so it can't be linked as child!");
        return false;
    }

    bool CConeAreaNode::OnLinkAsParentNodeAttempt(CScriptNode* child)
    {
        if(child->type != NODE_TYPE_EVENT)
        {
            conoutf(CON_DEBUG, "[box-area] a cone can only be linked as parent of an event node!");
        }
        return true;
    }

};
};
