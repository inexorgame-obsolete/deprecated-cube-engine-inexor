#include "inexor/flowgraph/areas/block/fl_area_block.h"

namespace inexor {
namespace vscript {


    CCubeAreaNode::CCubeAreaNode(vec start, vec end, const char* name, const char* comment)
    {
        type = NODE_TYPE_AREA_BLOCK;
        edge_start = start;
        edge_end = end;
    }

    
    CCubeAreaNode::~CCubeAreaNode()
    {
    }

    
    void CCubeAreaNode::reset()
    {
    }


    void CCubeAreaNode::render(int orient, bool sel_blocked)
    {
        // render box
        glBegin(GL_QUADS);


        glEnd();
    }

    bool CCubeAreaNode::collide(vec p)
    {
        return true;
    }

};
};
