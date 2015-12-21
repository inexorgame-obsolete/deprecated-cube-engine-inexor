#include "inexor/flowgraph/areas/sphere/fl_area_sphere.h"

namespace inexor {
namespace vscript {


    CSphereAreaNode::CSphereAreaNode(vec position, vec rad, const char* name, const char* comment)
    {
        type = NODE_TYPE_AREA_SPHERE;
        pos = position;
        radius = rad;
    }


    CSphereAreaNode::~CSphereAreaNode()
    {
    }


    void CSphereAreaNode::reset()
    {
    }


    void CSphereAreaNode::render(int orient, bool sel_blocked)
    {
        glBegin(GL_QUADS);
        // How to render a sphere correctly?
        glEnd();
    }

    bool CSphereAreaNode::collide(vec p)
    {
        return true;
    }

};
};
