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

/// Please note: creating nodes with Sauerbraten's standard entity system is shit.
/// Sooner or later the system will be rewritten for Hanack's new entity system. 

/// include guard
#ifndef INEXOR_VSCRIPT_NODEBASE_HEADER
#define INEXOR_VSCRIPT_NODEBASE_HEADER

/// c++ standard libraries
#include <string>
#include <vector>
#include <map>
#include <list>

/// Inexor namespace protection
namespace inexor {
namespace vscript {

/// the size of the quads which will be rendered as box
/// around the target node's position
const float boxsize = 4.0f;

/// enumeration of node types
enum VSCRIPT_NODE_TYPE
{
    NODE_TYPE_INVALID = -1, /// TODO: is this even reqired?
    NODE_TYPE_TIMER = 0,
    NODE_TYPE_COMMENT,
    NODE_TYPE_FUNCTION, /// TODO: ...
    NODE_TYPE_MEMORY,
    NODE_TYPE_IF,
    NODE_TYPE_SWITCH,
    NODE_TYPE_CONDITION,
};


/// color enumeration
enum VSCRIPT_NODE_COLORS
{
    VSCRIPT_COLOR_TIMER = 0x00B6FF,
    VSCRIPT_COLOR_COMMENT = 0x43A63A,
    VSCRIPT_COLOR_FUNCTION = 0xCE00CB,    
    /// 
    VSCRIPT_COLOR_TRIGGERED = 0xFF6D00,
};


/// @brief base class for node implementations
class script_node
{
    public:

    VSCRIPT_NODE_TYPE type;
    bool active;
    std::string node_name;
    std::string node_comment;
    vec position;
    bool pos_changed;
    bool selected;

    int default_box_color;
    int box_color;
    
    unsigned int this_time;
    unsigned int last_time;

    /// A standard constructor
    script_node() 
    {
        /// Please note that nodes are invalid by default.
        /// the constructor of the child classes needs to change this.
        type = NODE_TYPE_INVALID;
        active = true;       
        node_name = "";
        node_comment = "";        
        position = vec(0,0,0);
        pos_changed = false;
        selected = false;
        default_box_color = VSCRIPT_COLOR_TIMER; /// 
        box_color = default_box_color;
    }

    // TODO: Is a destructor required?
    ~script_node() {}

    /// Please note: You should make use of comments in your scripts whenever its required!

    /// A parent node gives me the incoming signal
    /// Now its my time for execution
    virtual void in() = 0;
    /// Run my stuff
    virtual void run() = 0;
    /// Now call outgoing 
    virtual void out() = 0;

    virtual void reset() = 0;

    /// We need Hanacks entity system at this point
    /// Relations with other nodes?

    /// All parent nodes
    std::vector<script_node*> incoming;
    /// All child nodes
    std::vector<script_node*> outgoing;
};

/// end of namespace
};
};

#endif
