/// @file fl_rendering.h
/// @author Johannes Schneider
/// @brief Node renderer using OpenGL and gle.

/// include guard
#ifndef INEXOR_VSCRIPT_RENDERING_HEADER
#define INEXOR_VSCRIPT_RENDERING_HEADER

//#include "inexor/flowgraph/debugger/fl_dbgrays.h"
#include "inexor/flowgraph/node/fl_nodebase.h"
#include "inexor/engine/engine.h"
#include <vector>

/// project's namespace protection
namespace inexor {
namespace vscript {

extern const float boxsize;

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
    protected:
        
    /// buffer for debug rays
    std::vector<debug_ray> rays;
        
    public:

    CVisualScriptRenderer();

    ~CVisualScriptRenderer();


    void adjust_selection_color(int orient, int index, int std_color_of_this_node);

    void renderbox(vec p, int orient, int std_color_of_this_node);

    void renderboxoutline(vec p);

    void renderboxhelplines(vec p);
};

/// end of namespace
};
};

#endif
