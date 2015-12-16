/// @file fl_rendering.h
/// @author Johannes Schneider
/// @brief Renderer for nodes and node relations

#ifndef INEXOR_VSCRIPT_NODE_RENDERER_HEADER
#define INEXOR_VSCRIPT_NODE_RENDERER_HEADER

#include "inexor/engine/engine.h"

namespace inexor {
namespace vscript {


    const float boxsize = 4.0f;


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

    enum VSCRIPT_NODE_COLORS
    {
        VSCRIPT_COLOR_TIMER     = 0x51ABCC,  // light blue
        VSCRIPT_COLOR_COMMENT   = 0x5BCC51,  // comment green
        VSCRIPT_COLOR_FUNCTION  = 0x51ABCC,  // darker purple
        VSCRIPT_COLOR_TRIGGERED = 0xFF8800,  // spicy orange
        VSCRIPT_COLOR_SLEEP     = 0x51ABCC,  
        VSCRIPT_COLOR_GRAY      = 0xAAAAAA,  // 
        VSCRIPT_COLOR_BLACK     = 0x000000,  // 
        VSCRIPT_COLOR_WHITE     = 0xFFFFFF,  // 
        VSCRIPT_COLOR_SELECTION = 0xFFFF4C,  // red 
        VSCRIPT_COLOR_DEBUG_RAY = 0x51ABCC,
    };


    class CNodeRenderer
    {

        public:
        
            CNodeRenderer();
            ~CNodeRenderer();

            VSCRIPT_NODE_COLORS box_color;
            VSCRIPT_NODE_COLORS default_box_color;


            void adjust_selection_color(int orient, int index);

            void render_box(vec p, int orient);

            void render_box_outline(vec p);

            void render_box_helplines(vec p);

    };

};
};

#endif
