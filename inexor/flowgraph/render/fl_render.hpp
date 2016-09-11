/// @file fl_rendering.hpp
/// @author Johannes Schneider
/// @brief Renderer for nodes and node relations

#ifndef INEXOR_VSCRIPT_NODE_RENDERER_HEADER
#define INEXOR_VSCRIPT_NODE_RENDERER_HEADER

#include "inexor/engine/engine.hpp"


namespace inexor {
namespace vscript {

    const float boxsize = 5.0f;

    enum INEXOR_VSCRIPT_ENTITY_BOX_ORIENTATION
    {
        INEXOR_VSCRIPT_BOX_NO_INTERSECTION = -1,
        INEXOR_VSCRIPT_BOX_LEFT,
        INEXOR_VSCRIPT_BOX_RIGHT,
        INEXOR_VSCRIPT_BOX_FRONT,
        INEXOR_VSCRIPT_BOX_BACK,
        INEXOR_VSCRIPT_BOX_BOTTOM,
        INEXOR_VSCRIPT_BOX_TOP
    };


    enum INEXOR_VSCRIPT_NODE_COLORS
    {
        INEXOR_VSCRIPT_COLOR_TIMER     = 0x51ABCC,  // light blue
        INEXOR_VSCRIPT_COLOR_COMMENT   = 0x5BCC51,  // comment green
        INEXOR_VSCRIPT_COLOR_FUNCTION  = 0x51ABCC,  // darker purple
        INEXOR_VSCRIPT_COLOR_TRIGGERED = 0xFF8800,  // spicy orange
                                                    //0x00D137
        INEXOR_VSCRIPT_COLOR_SLEEP     = 0x51ABCC,  // spicy blue
        INEXOR_VSCRIPT_COLOR_GRAY      = 0xAAAAAA,  // gray
        INEXOR_VSCRIPT_COLOR_BLACK     = 0x000000,  // black
        INEXOR_VSCRIPT_COLOR_WHITE     = 0xFFFFFF,  // white
        INEXOR_VSCRIPT_COLOR_SELECTION = 0xFFFF4C,  // white yellow 
        INEXOR_VSCRIPT_COLOR_DEBUG_RAY = 0x51ABCC,  // spicy blue
        INEXOR_VSCRIPT_COLOR_MEMORY    = 0xFF3D91,  // purple
        INEXOR_VSCRIPT_COLOR_AREA      = 0xFFFFFF,  // = 0x1900FF,
        INEXOR_VSCRIPT_COLOR_PENDING   = 0xFF263F,  // light red
        INEXOR_VSCRIPT_COLOR_OPERATOR  = 0x9451CC,  // purple
    };


    class CNodeRenderer
    {

        public:

            CNodeRenderer();
            ~CNodeRenderer();

            INEXOR_VSCRIPT_NODE_COLORS box_color;
            INEXOR_VSCRIPT_NODE_COLORS triggered_color;
            INEXOR_VSCRIPT_NODE_COLORS default_box_color;

            void adjust_selection_color(int orient, int index);
            void render_box(vec p, int orient);
            void render_box_outline(vec p);
            void render_box_helplines(vec p);

    };

};
};

#endif
