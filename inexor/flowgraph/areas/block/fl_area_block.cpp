#include "inexor/flowgraph/areas/block/fl_area_block.hpp"

namespace inexor {
namespace vscript {
    

    CCubeAreaNode::CCubeAreaNode(vec position, vec edge_vector, const char* name, const char* comment)
    {
        type = NODE_TYPE_AREA_BLOCK;
        pos = position;
        edge = edge_vector;
    }

    CCubeAreaNode::~CCubeAreaNode()
    {
    }


    // render cube by position and its edge
    void CCubeAreaNode::render(int orient, bool sel_blocked)
    {
        vec p = pos;
        vec e = edge;
        glBegin(GL_QUADS);

        glVertex3f(p.x,p.y,p.z+e.z);
        glVertex3f(p.x+e.x,p.y,p.z+e.z);
        glVertex3f(p.x+e.x,p.y+e.y,p.z+e.z);
        glVertex3f(p.x,p.y+e.y,p.z+e.z);

        glVertex3f(p.x,p.y+e.y,p.z);
        glVertex3f(p.x+e.x,p.y+e.y,p.z);
        glVertex3f(p.x+e.x,p.y,p.z);
        glVertex3f(p.x,p.y,p.z);

        glVertex3f(p.x,p.y,p.z);
        glVertex3f(p.x+e.x,p.y,p.z);
        glVertex3f(p.x+e.x,p.y,p.z+e.z);
        glVertex3f(p.x,p.y,p.z+e.z);

        glVertex3f(p.x,p.y+e.y,p.z+e.z);
        glVertex3f(p.x+e.x,p.y+e.y,p.z+e.z);
        glVertex3f(p.x+e.x,p.y+e.y,p.z);
        glVertex3f(p.x,p.y+e.y,p.z);

        glVertex3f(p.x,p.y,p.z+e.z);
        glVertex3f(p.x,p.y+e.y,p.z+e.z);
        glVertex3f(p.x,p.y+e.y,p.z);
        glVertex3f(p.x,p.y,p.z);

        glVertex3f(p.x+e.x,p.y,p.z);
        glVertex3f(p.x+e.x,p.y+e.y,p.z);
        glVertex3f(p.x+e.x,p.y+e.y,p.z+e.z);
        glVertex3f(p.x+e.x,p.y,p.z+e.z);
        glEnd();
    }


    bool CCubeAreaNode::collide(vec p)
    {
        return true;
    }

};
};
