#include "inexor/flowgraph/areas/block/fl_area_block.hpp"

namespace inexor {
namespace vscript {
    

    CCubeAreaNode::CCubeAreaNode(vec position, float width, float height, float depth, const char* name, const char* comment = "")
    {
        type = NODE_TYPE_AREA_BOX;
        pos = position;
        node_name = name;
        node_comment = comment;

        box_width = width;
        box_height = height;
        box_depth = depth;
    }


    CCubeAreaNode::~CCubeAreaNode()
    {
    }


    bool CCubeAreaNode::collide(vec p)
    {
        return true;
    }


    void CCubeAreaNode::render_additional()
    {
        gle::color(vec::hexcolor(VSCRIPT_AREA));
        glBegin(GL_LINES);

        float offsetx = - (box_width/2) + (boxsize/2);
        float offsety = - (box_depth/2) + (boxsize/2);
        float offsetz = - (box_height/2) + (boxsize/2);


        // horizontal x lines
        glVertex3f(offsetx + pos.x,             offsety + pos.y,             offsetz + pos.z);
        glVertex3f(offsetx + pos.x + box_width, offsety + pos.y,             offsetz + pos.z);

        glVertex3f(offsetx + pos.x,             offsety + pos.y + box_depth, offsetz + pos.z);
        glVertex3f(offsetx + pos.x + box_width, offsety + pos.y + box_depth, offsetz + pos.z);

        glVertex3f(offsetx + pos.x,             offsety + pos.y,             offsetz + pos.z + box_height);
        glVertex3f(offsetx + pos.x + box_width, offsety + pos.y,             offsetz + pos.z + box_height);

        glVertex3f(offsetx + pos.x,             offsety + pos.y + box_depth, offsetz + pos.z + box_height);
        glVertex3f(offsetx + pos.x + box_width, offsety + pos.y + box_depth, offsetz + pos.z + box_height);


        // vertical lines
        glVertex3f(offsetx + pos.x, offsety + pos.y, offsetz + pos.z);
        glVertex3f(offsetx + pos.x, offsety + pos.y, offsetz + pos.z + box_height);

        glVertex3f(offsetx + pos.x + box_width, offsety + pos.y, offsetz + pos.z);
        glVertex3f(offsetx + pos.x + box_width, offsety + pos.y, offsetz + pos.z + box_height);

        glVertex3f(offsetx + pos.x, offsety + pos.y + box_depth, offsetz + pos.z);
        glVertex3f(offsetx + pos.x, offsety + pos.y + box_depth, offsetz + pos.z + box_height);

        glVertex3f(offsetx + pos.x + box_width, offsety + pos.y + box_depth, offsetz + pos.z);
        glVertex3f(offsetx + pos.x + box_width, offsety + pos.y + box_depth, offsetz + pos.z + box_height);


        // horizontal y lines
        glVertex3f(offsetx + pos.x, offsety + pos.y, offsetz + pos.z);
        glVertex3f(offsetx + pos.x, offsety + pos.y + box_depth, offsetz + pos.z);

        glVertex3f(offsetx + pos.x + box_width, offsety + pos.y, offsetz + pos.z);
        glVertex3f(offsetx + pos.x + box_width, offsety + pos.y + box_depth, offsetz + pos.z);

        glVertex3f(offsetx + pos.x, offsety + pos.y, offsetz + pos.z + box_height);
        glVertex3f(offsetx + pos.x, offsety + pos.y + box_depth, offsetz + pos.z + box_height);

        glVertex3f(offsetx + pos.x + box_width, offsety + pos.y, offsetz + pos.z + box_height);
        glVertex3f(offsetx + pos.x + box_width, offsety + pos.y + box_depth, offsetz + pos.z + box_height);

        glEnd();
    }



    bool CCubeAreaNode::OnLinkAsChildNodeAttempt(CScriptNode* parent)
    {
        conoutf(CON_DEBUG, "[box-area] a box area can't run any code so it can't be linked as child!");
        return false;
    }

    bool CCubeAreaNode::OnLinkAsParentNodeAttempt(CScriptNode* child)
    {
        if(child->type != NODE_TYPE_EVENT)
        {
            conoutf(CON_DEBUG, "[box-area] a box can only be linked as parent of an event node!");
        }
        return true;
    }

};
};
