#include "inexor/flowgraph/areas/cylinder/fl_area_cylinder.hpp"

namespace inexor {
namespace vscript {

    CCylinderAreaNode::CCylinderAreaNode(vec position, float radius, float height, const char* name, const char* comment = "")
    {
        type = INEXOR_VSCRIPT_NODE_TYPE_AREA_BOX;
        pos = position;
        node_name = name;
        node_comment = comment;
        cylinder_height = height;
        cylinder_radius = radius;
    }

    CCylinderAreaNode::~CCylinderAreaNode()
    {
    }

    bool CCylinderAreaNode::collide(vec p)
    {
        return true;
    }

    void CCylinderAreaNode::render_additional()
    {
        gle::color(vec::hexcolor(INEXOR_VSCRIPT_COLOR_AREA));

        glBegin(GL_LINE_LOOP);
        loopi(render_detail_level)
        {
            vec tmp = vec(pos).rotate(2 * M_PI*i / render_detail_level, vec(0,1,0));
            glVertex3f(tmp.x, tmp.y, tmp.z);
        }
        glEnd();
    }

    bool CCylinderAreaNode::OnLinkAsChildNodeAttempt(CScriptNode* parent)
    {
        conoutf(CON_DEBUG, "[3DVS-cylinderarea] a cone area can't run any code so it can't be linked as child!");
        return false;
    }

    bool CCylinderAreaNode::OnLinkAsParentNodeAttempt(CScriptNode* child)
    {
        if(child->type != INEXOR_VSCRIPT_NODE_TYPE_EVENT)
        {
            conoutf(CON_DEBUG, "[3DVS-cylinderarea] a cone can only be linked as parent of an event node!");
        }
        return true;
    }

};
};
