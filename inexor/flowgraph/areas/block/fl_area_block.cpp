#include "inexor/flowgraph/areas/block/fl_area_block.h"

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

    
    void CCubeAreaNode::reset()
    {
    }


    void CCubeAreaNode::render(int orient, bool sel_blocked)
    {
        // render cube
        vec p = pos;
        vec e = edge;
        
        glBegin(GL_QUADS);
        
        glColor3f(1.0f,0.0f,0.0f);

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
