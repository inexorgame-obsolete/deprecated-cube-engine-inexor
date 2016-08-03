#include "inexor/flowgraph/areas/cone/fl_area_cone.hpp"

namespace inexor {
namespace vscript {

    CConeAreaNode::CConeAreaNode(vec position, float radius, float height, const char* name, const char* comment = "")
    {
        type = INEXOR_VSCRIPT_NODE_TYPE_AREA_BOX;
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
        // TODO: buggy
        if (cone_radius <= 0) return;
        vec dir = vec(pos).sub(vec(0,0,+1)).normalize();
        float angle = 1.0f;
        vec spot = vec(dir).mul(cone_radius*cosf(angle*RAD)).add(pos), spoke;
        spoke.orthogonal(dir);
        spoke.normalize();
        spoke.mul(cone_radius*sinf(angle*RAD));

        gle::color(vec::hexcolor(INEXOR_VSCRIPT_COLOR_AREA));

        glBegin(GL_LINES);
        loopi(render_detail_level)
        {
            glVertex3f(pos.x, pos.y, pos.z);
            vec end_point = vec(spoke).rotate(2 * M_PI*i / render_detail_level, dir).add(spot);
            glVertex3f(end_point.x, end_point.y, end_point.z);
        }
        glEnd();

        glBegin(GL_LINE_LOOP);
        loopi(render_detail_level)
        {
            vec tmp = vec(spoke).rotate(2 * M_PI*i / render_detail_level, dir).add(spot);
            glVertex3f(tmp.x, tmp.y, tmp.z);
        }
        glEnd();
    }

    bool CConeAreaNode::OnLinkAsChildNodeAttempt(CScriptNode* parent)
    {
        conoutf(CON_DEBUG, "[3DVS-boxarea] a cone area can't run any code so it can't be linked as child!");
        return false;
    }

    bool CConeAreaNode::OnLinkAsParentNodeAttempt(CScriptNode* child)
    {
        if(child->type != INEXOR_VSCRIPT_NODE_TYPE_EVENT)
        {
            conoutf(CON_DEBUG, "[3DVS-boxarea] a cone can only be linked as parent of an event node!");
        }
        return true;
    }

};
};
