/// @file fl_rendering.h
/// @author Johannes Schneider
/// @brief Renderer for nodes and node relations

#ifndef INEXOR_VSCRIPT_NODE_RENDERER_HEADER
#define INEXOR_VSCRIPT_NODE_RENDERER_HEADER

 #include <vector>
 
 #include "inexor/flowgraph/node/fl_nodebase.h"
 #include "inexor/flowgraph/debugger/fl_dbgrays.h"
 #include "inexor/flowgraph/timer/fl_timer.h"
 #include "inexor/engine/engine.h"


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

    class CNodeRenderer
    {

        public:
        
            std::vector<CDebugRay> rays;

            CNodeRenderer();

            ~CNodeRenderer();

            void start_rendering();

            void end_rendering();

            void adjust_selection_color(int orient, int index, CScriptNode* node);

            void renderbox(CScriptNode* node, int orient);

            void renderboxoutline(vec p);

            void renderboxhelplines(vec p);

            void render_debug_rays();
    };

};
};

#endif
