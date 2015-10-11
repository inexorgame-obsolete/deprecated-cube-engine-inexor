/// @file fl_timer.h (flowgraph's timer implementation)
/// @author Johannes Schneider
/// @brief Timers will be called every [n] miliseconds


/// include guard
#ifndef INEXOR_VSCRIPT_RENDERING_HEADER
#define INEXOR_VSCRIPT_RENDERING_HEADER

/// project's namespace protection
namespace inexor {
namespace vscript {

/// box side selection indices
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


/// 
/// 
/// 
/// 
class CVisualScriptRenderer
{
    CVisualScriptRenderer();
    ~CVisualScriptRenderer();

    void adjust_selection_color(int orient, int index);
    void renderbox(vec p, int orient);
    void renderboxoutline(vec p);
    void renderboxhelplines(vec p);
};

}; // end of namespace protection
};

#endif