/// @file fl_nodebase.h
/// @author Johannes Schneider
/// @brief Basic implementation of nodes in Inexor's 3D Visual Scripting System
/// 
/// .-------------------------------------------------------------------------------------------------.
/// | Basic node implementation                                                                       |
/// |_________________________________________________________________________________________________|
/// |                                                                                                 |
/// | Every node inherits its basic members and methods from this base class.                         |
/// | This base class manages the basic behaviour of nodes.                                           |
/// |_________________________________________________________________________________________________|
/// |                                                                                                 |
/// | The following members and methods will be inherited from every child class:                     |
/// |                                                                                                 |
/// | type          the type of the node (see VSCRIPT_NODE_TYPE enumeration).                         |
/// | selected      indicates if this node is selected by the editor. (TODO..)                        |
/// | pos           the position of the node in 3D space.                                             |
/// | active        indicates if this node is active for execution (TODO..)                           |
/// | node_name     a customizable name for this node. (TODO..)                                       |
/// | node_comment  a comment on this node. (TODO..)                                                  |
/// |                                                                                                 |
/// ._________________________________________________________________________________________________.
///

/// Please note: creating nodes with Sauerbraten's standard entity system does suck.
/// TODO: sooner or later the system will be rewritten based on Hanack's new entity system. 

/// include guard
#ifndef INEXOR_VSCRIPT_NODEBASE_HEADER
#define INEXOR_VSCRIPT_NODEBASE_HEADER

#include "inexor/engine/engine.h"

/// time conversion tools
#include "inexor/flowgraph/time/fl_time.h"


/// c++ standard libraries
#include <string>
#include <vector>
#include <map>
#include <list>


/// Inexor namespace protection
namespace inexor {
namespace vscript {

/// The node entity's box size
const float boxsize = 3.0f;

/// enumeration of node types
enum VSCRIPT_NODE_TYPE
{
    NODE_TYPE_INVALID = -1, /// TODO: Is this type even neccesary?
    NODE_TYPE_TIMER = 0,
    NODE_TYPE_COMMENT,
    NODE_TYPE_FUNCTION,
    NODE_TYPE_MEMORY,
    NODE_TYPE_IF,
    NODE_TYPE_SWITCH,
    NODE_TYPE_CONDITION,
    NODE_TYPE_SLEEP,
};


/// Enumeration of color codes in RGB integer format
enum VSCRIPT_NODE_COLORS
{
    /// Node type colors
    VSCRIPT_COLOR_TIMER     = 0x00B6FF,
    VSCRIPT_COLOR_COMMENT   = 0x43A63A,
    VSCRIPT_COLOR_FUNCTION  = 0xCC47B1,    
    VSCRIPT_COLOR_TRIGGERED = 0xFF6D00,
    VSCRIPT_COLOR_GRAY      = 0xAAAAAA,
    VSCRIPT_COLOR_BLACK     = 0x000000,
};

/// @brief base class for node implementations
class script_node
{
    public:

    script_node();

    ~script_node();
    
    /// @see VSCRIPT_NODE_COLORS
    VSCRIPT_NODE_TYPE type;

    std::string node_name;
    std::string node_comment;

    bool active;
    bool pos_changed;
    bool selected;

    vec position;

    /// Rendering 
    int default_box_color;
    int box_color;

    /// Timing management
    unsigned int this_time;
    unsigned int last_time;

    /// Please note: You should make use of comments in your scripts whenever its required!

    /// A parent node gives me the incoming signal
    /// Now its my time for execution
    virtual void in() = 0;
    /// Run my stuff
    virtual void run() = 0;
    /// Now call outgoing 
    virtual void out() = 0;
    /// Reset this node
    virtual void reset() = 0;

    /// A vector of pointers to parent nodes
    std::vector<script_node *> incoming;

    /// A vector of pointers to child nodes
    std::vector<script_node *> outgoing;
};

/// end of namespace
};
};

#endif
