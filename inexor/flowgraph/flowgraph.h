/// @file flowgraph.h
/// @author Johannes Schneider
/// @brief 3D visual scripting system

/// include guard
#ifndef INEXOR_VSCRIPT_HEADER
#define INEXOR_VSCRIPT_HEADER

/// include Inexor game engine
#include "inexor/engine/engine.h"


/// basic script node
#include "inexor/flowgraph/node/fl_nodebase.h"
/// timer implementation
#include "inexor/flowgraph/timer/fl_timer.h"
/// debug rays
#include "inexor/flowgraph/debugger/fl_dbgrays.h"
/// comments
#include "inexor/flowgraph/comment/fl_comment.h"
/// renderer
#include "inexor/flowgraph/renderer/fl_rendering.h"


/// project's namespace protection
namespace inexor {
namespace vscript {


/// pre declarations
void node_render_test();
void notify_flowgraph_mouse_key_change(int, bool);
bool is_flowgraph_entity_selected();


/// the size of the quads which will be rendered as box
/// around the target node's position
const float boxsize = 4.0f;


/// @brief Visual Script System
class CVisualScriptSystem //: public CVisualScriptRenderer
{
    public:

    CVisualScriptSystem();
    ~CVisualScriptSystem();

    /// buffer for nodes
    std::vector<script_node *> nodes;

    /// the selected node
    script_node* selected_node;
    /// entity selection?
    bool selected = false;

    /// add a node
    void add_node(char*,char*,char*,char*);
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
    ///void change_property(propid ID, const char* val);
};

};
};

#endif /// INEXOR_VSCRIPT_HEADER
