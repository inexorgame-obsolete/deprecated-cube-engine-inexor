/// @file fl_rendering.h
/// @author Johannes Schneider
/// @brief Renderer for nodes and node relations

#ifndef INEXOR_VSCRIPT_RENDERING_HEADER
#define INEXOR_VSCRIPT_RENDERING_HEADER

#include <vector>

#include "inexor/engine/engine.h"
#include "inexor/flowgraph/node/fl_nodebase.h"


namespace inexor {
namespace vscript {

    extern const float boxsize;


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

            std::vector<CDebugRay> rays;

            void adjust_selection_color(int orient, int index, CScriptNode *node);

            void renderbox(CScriptNode *node, int orient);
            void renderboxoutline(vec p);
            void renderboxhelplines(vec p);

            void render_debug_rays();

        public:

            CVisualScriptRenderer();
            ~CVisualScriptRenderer();
    
            void start_rendering();

            virtual void render_nodes() = 0;
            virtual void render_node_relations() = 0;

            void end_rendering();
    };

};
};

#endif
