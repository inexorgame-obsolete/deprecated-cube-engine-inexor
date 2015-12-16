#include "inexor/flowgraph/areas/cube/fl_area_cube.h"

namespace inexor {
namespace vscript {


    CCubeArea::CCubeArea()
    {
        edge_start = vec(0,0,0);
        edge_end = vec(0,0,0);
    }

    CCubeArea::~CCubeArea()
    {
    }

    bool collide(vec p)
    {
        return true;
    }

};
};
