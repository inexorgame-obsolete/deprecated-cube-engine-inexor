/// @file flowgraph.h
/// @author Johannes Schneider
/// @brief 3D visual scripting system

#ifndef INEXOR_VSCRIPT_FLOWGRAPH_HEADER
#define INEXOR_VSCRIPT_FLOWGRAPH_HEADER

#include <deque>
#include <vector>
#include <stdarg.h>

#include "inexor/flowgraph/node/fl_nodebase.h"
#include "inexor/flowgraph/renderer/fl_noderenderer.h"
#include "inexor/flowgraph/editor/fl_enteditor.h"
 #include "inexor/flowgraph/debugger/fl_dbgrays.h"


namespace inexor {
namespace vscript {

    class CVisualScriptSystem : public CEntityManager
    {
        protected:
            void update_input(int, bool);

        public:
        
            std::vector<CScriptNode *> nodes;
            std::vector<CDebugRay> rays;

            CVisualScriptSystem();
            ~CVisualScriptSystem();

            CScriptNode* add_node(VSCRIPT_NODE_TYPE type, int parameter_count, ...);

            
            void start_rendering();
            void end_rendering();

            void render_nodes();
            void render_node_relations();
            void render_debug_rays();

            void update_timers();

            void connect_nodes(CScriptNode *from, CScriptNode *to);

            void update_drag_n_drop();
            void sync_all_timers();
            void delete_all_nodes();
    };

};
};

#endif
