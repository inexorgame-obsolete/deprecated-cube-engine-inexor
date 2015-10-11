/// @file fl_timer.h (flowgraph's timer implementation)
/// @author Johannes Schneider
/// @brief Timers will be called every [n] miliseconds

/// include guard
#ifndef INEXOR_VSCRIPT_RENDERING_HEADER
#define INEXOR_VSCRIPT_RENDERING_HEADER

//#include "inexor/flowgraph/debugger/fl_dbgrays.h"
#include "inexor/engine/engine.h"
#include <vector>

/// project's namespace protection
namespace inexor {
namespace vscript {


/// the size of the quads which will be rendered as box
/// around the target node's position
const float boxsize = 4.0f;

/// box side selection indices (defined by Cube engine)
enum VSCRIPT_ENTITY_BOX_ORIENTATION
{
    VSCRIPT_BOX_NO_INTERSECTION = -1,
    VSCRIPT_BOX_LEFT,
    VSCRIPT_BOX_RIGHT,
    VSCRIPT_BOX_FRONT,
    VSCRIPT_BOX_BACK,
    VSCRIPT_BOX_BOTTOM,
    VSCRIPT_BOX_TOP
};

/// Visual Scripting Renderer
class CVisualScriptRenderer
{
    public:

    /// constructor
    CVisualScriptRenderer();
    /// destuctor
    ~CVisualScriptRenderer();

    /// buffer for debug rays
    //std::vector<debug_ray> rays;

    void adjust_selection_color(int orient, int index);

    void renderbox(vec p, int orient);

    void renderboxoutline(vec p);

    void renderboxhelplines(vec p);
};


};
};

#endif
