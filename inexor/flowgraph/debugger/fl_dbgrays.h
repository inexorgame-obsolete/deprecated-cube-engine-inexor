/// @file fl_timer.h (flowgraph's timer implementation)
/// @author Johannes Schneider
/// @brief Debug rays help to understand the position of new placed nodes.

/// include guard
#ifndef INEXOR_VSCRIPT_DEBUGRAY_HEADER
#define INEXOR_VSCRIPT_DEBUGRAY_HEADER

#include "inexor/flowgraph/node/fl_nodebase.h"

/// project's namespace protection
namespace inexor {
namespace vscript {

/// ray renderer shows your current camera position
/// and the position of your selection and renders
/// a ray.
class debug_ray
{
    public:
    vec pos;
    vec target;
};

// end of namespace protection
};
};

#endif
