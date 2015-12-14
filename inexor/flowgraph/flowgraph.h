/// @file flowgraph.h
/// @author Johannes Schneider
/// @brief 3D visual scripting system

#ifndef INEXOR_VSCRIPT_HEADER
#define INEXOR_VSCRIPT_HEADER

#include <stdarg.h>
#include <deque>

#include "inexor/engine/engine.h"

#include "inexor/flowgraph/node/fl_nodebase.h"
#include "inexor/flowgraph/debugger/fl_dbgrays.h"
#include "inexor/flowgraph/comment/fl_comment.h"
#include "inexor/flowgraph/functions/fl_functions.h"
#include "inexor/flowgraph/renderer/fl_noderenderer.h"
#include "inexor/flowgraph/editor/fl_enteditor.h"
#include "inexor/flowgraph/timer/fl_timer.h"
#include "inexor/flowgraph/sleep/fl_sleep.h"
#include "inexor/flowgraph/worker/fl_threadworker.h"


namespace inexor {
namespace vscript {

    class CVisualScriptSystem : public CVisualScriptRenderer, public CEntityManager
    {
        public:
        
            CVisualScriptSystem();
            ~CVisualScriptSystem();

            std::vector<CScriptNode *> nodes;

            unsigned int unique_execution_pass_timestamp;

            CScriptNode* add_node(VSCRIPT_NODE_TYPE type, int parameter_count, ...);

            // implementation of the inherited virtual functions
            void render_node_relations();
            void render_nodes();
            void render_debug_rays();
            void process_change(int, bool);

            void connect_nodes(CScriptNode *from, CScriptNode *to);
            void disconnect_nodes(CScriptNode *from, CScriptNode *to);

            void update_drag_n_drop();
            void sync_all_timers();
            void delete_all_nodes();
    };

};
};

#endif
