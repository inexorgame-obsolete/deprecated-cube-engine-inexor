/// @file flowgraph.h
/// @author Johannes Schneider
/// @brief 3D visual scripting system

#ifndef INEXOR_VSCRIPT_FLOWGRAPH_HEADER
#define INEXOR_VSCRIPT_FLOWGRAPH_HEADER

#include <deque>
#include <vector>
#include <stdarg.h>

/// ------------------------------------------------------------------
#include "inexor/flowgraph/node/fl_nodebase.h"

#include "inexor/flowgraph/timer/fl_timer.h"
#include "inexor/flowgraph/sleep/fl_sleep.h"
#include "inexor/flowgraph/comment/fl_comment.h"
#include "inexor/flowgraph/functions/fl_functionbase.h"
#include "inexor/flowgraph/functions/fl_functions.h"

#include "inexor/flowgraph/editor/fl_enteditor.h"

#include "inexor/flowgraph/renderer/fl_noderenderer.h"

#include "inexor/fpsgame/game.h"

/// ------------------------------------------------------------------

namespace inexor {
namespace vscript {

    class CVisualScriptSystem : public CEntityManager, public CNodeRenderer
    {
        public:
        
            std::vector<CScriptNode *> nodes;

            CVisualScriptSystem();
            ~CVisualScriptSystem();

            CScriptNode* add_node(VSCRIPT_NODE_TYPE type, int parameter_count, ...);

            void render_nodes();
            void render_node_relations();

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
