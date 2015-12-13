// @file fl_rendering.h
// @author Johannes Schneider
// @brief Node renderer using OpenGL and gle.

#ifndef INEXOR_VSCRIPT_RENDERING_HEADER
#define INEXOR_VSCRIPT_RENDERING_HEADER

#include "inexor/engine/engine.h"
#include <vector>

#include "inexor/flowgraph/node/fl_nodebase.h"


namespace inexor {
namespace vscript {

    extern const float boxsize;

    // box side selection indices (defined by Cube Engine!)
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


    class CVisualScriptRenderer
    {
        protected:

            void adjust_selection_color(int orient, int index, CScriptNode *node);

        public:

            CVisualScriptRenderer();
            ~CVisualScriptRenderer();
    
            void start_rendering();

            void renderbox(CScriptNode *node, int orient);
            void renderboxoutline(vec p);
            void renderboxhelplines(vec p);
            void render_debug_rays();

            virtual void render_nodes() = 0;
            virtual void render_node_relations() = 0;

            void end_rendering();
    };

};
};

#endif
