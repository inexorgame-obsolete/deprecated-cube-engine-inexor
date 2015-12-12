/// @file fl_rendering.h
/// @author Johannes Schneider
/// @brief Node renderer using OpenGL and gle.

#ifndef INEXOR_VSCRIPT_RENDERING_HEADER
#define INEXOR_VSCRIPT_RENDERING_HEADER

#include "inexor/engine/engine.h"
#include <vector>

/// project's namespace protection
namespace inexor {
namespace vscript {

    extern const float boxsize;

    /// box side selection indices (defined by Cube Engine!)
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


    /// Visual Scripting Box and Relation Curve Renderer
    class CVisualScriptRenderer
    {
        protected:

            void adjust_selection_color(int orient, int index, int std_color_of_this_node);

        public:

            CVisualScriptRenderer();
            ~CVisualScriptRenderer();
    
            void start_rendering();

            void renderbox(vec p, int orient, int std_color_of_this_node);
            void renderboxoutline(vec p);
            void renderboxhelplines(vec p);

            virtual void render_nodes() = 0;
            virtual void render_node_relations() = 0;

            void end_rendering();
    };

};
};

#endif
