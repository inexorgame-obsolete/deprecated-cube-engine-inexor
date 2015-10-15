/// @file flowgraph.h
/// @author Johannes Schneider
/// @brief 3D visual scripting system

/// include guard
#ifndef INEXOR_VSCRIPT_HEADER
#define INEXOR_VSCRIPT_HEADER

#include "inexor/engine/engine.h"

#include "inexor/flowgraph/node/fl_nodebase.h"
#include "inexor/flowgraph/timer/fl_timer.h"
#include "inexor/flowgraph/debugger/fl_dbgrays.h"
#include "inexor/flowgraph/comment/fl_comment.h"
#include "inexor/flowgraph/functions/fl_functions.h"
#include "inexor/flowgraph/renderer/fl_rendering.h"

/// We need variable parameter lists
#include <stdarg.h>

/// project's namespace protection
namespace inexor {
namespace vscript {

/// TODO: remove forward???
class CVisualScriptRenderer;

/// @brief Visual Script System
class CVisualScriptSystem
{
    public:

    CVisualScriptSystem();
    ~CVisualScriptSystem();

    /// node rendering
    CVisualScriptRenderer renderer;

    /// buffer for nodes
    std::vector<script_node *> nodes;

    /// TODO: do we need this for entity selection?
    bool selected = false;

    /// the selected node
    script_node* selected_node;
    script_node* hover_node;

    /// Please note: add_node is using variable argument lists. See stdarg.h

    /// add a node
    script_node* add_node(VSCRIPT_NODE_TYPE type, int parameter_count, ...);

    /// Link nodes with other nodes
    void connect_nodes(script_node *from, script_node *to);
    void mouse_event_notifyer(int code, bool isdown);

    /// Please note: this will prevent timers from becoming not synchronized
    unsigned int unique_execution_pass_timestamp;
    void check_timers_and_events();

    /// TODO: profiling and benchmarking?

    /// synchronise timers
    void sync_timers();

    /// Rendering
    void start_rendering();
    void end_rendering();

    /// TODO: move rendering completely to fl_rendering.h and refactor!

    /// render nodes
    void render_nodes();
    /// render relations
    void render_node_relations();
    /// render curves
    void render_bezier_curves();

    /// remove all nodes
    /// and relations
    void clear_nodes();

    /// TODO: change entity properties
    /// void change_property(propid ID, const char* val);
};

};
};

#endif /// INEXOR_VSCRIPT_HEADER
