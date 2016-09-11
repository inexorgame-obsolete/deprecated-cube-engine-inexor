#include "inexor/flowgraph/areas/box/fl_area_box.hpp"

namespace inexor {
namespace vscript {
    
    CBoxAreaNode::CBoxAreaNode(vec position, float width, float height, float depth)
    {
        type = INEXOR_VSCRIPT_NODE_TYPE_AREA_BOX;
        pos = position;
        box_width = width;
        box_height = height;
        box_depth = depth;
    }
    
    CBoxAreaNode::~CBoxAreaNode()
    {
    }


    bool CBoxAreaNode::is_point_inside_box(vec point_pos)
    {
        vec p = point_pos;
        vec c = pos;
        return p.x>(c.x - (box_width/2))   && p.x<(c.x + (box_width/2)) &&
               p.y>(c.y - (box_height/2)) && p.y<(c.y + (box_height/2)) &&
               p.z>(c.z - (box_depth/2))  && p.z<(c.z + (box_depth/2));
    }

    void CBoxAreaNode::render_additional()
    {
        gle::color(vec::hexcolor(INEXOR_VSCRIPT_COLOR_AREA));
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

    bool CBoxAreaNode::OnLinkAsChildNodeAttempt(CScriptNode* parent)
    {
        conoutf(CON_DEBUG, "[3DVS-area-box] a box area can't run any code so it can't be linked as child node!");
        return false;
    }

    bool CBoxAreaNode::OnLinkAsParentNodeAttempt(CScriptNode* child)
    {
        if(INEXOR_VSCRIPT_NODE_TYPE_EVENT != child->type)
        {
            conoutf(CON_DEBUG, "[3DVS-area-box] a box can only be linked as parent of an event node!");
        }
        return true;
    }

};
};
