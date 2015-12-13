// @file flowgraph.h
// @author Johannes Schneider
// @brief 3D visual scripting system

#ifndef INEXOR_VSCRIPT_HEADER
#define INEXOR_VSCRIPT_HEADER

// variable parameter lists
#include <stdarg.h>

#include <deque>

#include "inexor/engine/engine.h"

#include "inexor/flowgraph/node/fl_nodebase.h"
#include "inexor/flowgraph/debugger/fl_dbgrays.h"
#include "inexor/flowgraph/comment/fl_comment.h"
#include "inexor/flowgraph/functions/fl_functions.h"
#include "inexor/flowgraph/renderer/fl_rendering.h"
#include "inexor/flowgraph/editor/fl_enteditor.h"
#include "inexor/flowgraph/timer/fl_timer.h"
#include "inexor/flowgraph/sleep/fl_sleep.h"
#include "inexor/flowgraph/worker/fl_threadworker.h"


// TODO: profiling and benchmarking?
// TODO: change entity properties (We really need Hanack's new entity system here)
// TODO: add and remove nodes


namespace inexor {
namespace vscript {

    class CVisualScriptSystem : public CVisualScriptRenderer, public CEntityManager
    {
        public:

            bool geometrie_vor_der_nase;

            CVisualScriptSystem();
            ~CVisualScriptSystem();

            std::vector<CScriptNode *> nodes;

            // Please note: add_node is using variable argument lists. See stdarg.h
            // add a node to the system
            // @param type the type of the integer
            // problem: parameter specification requires new command line code!
            // we must get rid of this old 5 attributes stuff
            // this code has been debugged and tested
            CScriptNode* add_node(VSCRIPT_NODE_TYPE type, int parameter_count, ...);

            // implementation of inherited virtual functions
            void render_node_relations();
            void render_nodes();
            void process_change(int, bool);

            // Link nodes with other nodes
            void connect_nodes(CScriptNode *from, CScriptNode *to);

            // Please note: this will prevent timers from being desynchronized
            unsigned int unique_execution_pass_timestamp;
            void update_timers_and_events();
            void sync_all_timers();
            void clear_all_nodes();
    };

};
};

#endif
