/// @file fl_timer.h (flowgraph's timer implementation)
/// @author Johannes Schneider
/// @brief Basic implementation of (visual) script nodes

/// include guard
#ifndef INEXOR_VSCRIPT_NODEBASE_HEADER
#define INEXOR_VSCRIPT_NODEBASE_HEADER

/// project's namespace protection
namespace inexor {
namespace vscript {

/// enumeration of node types
enum VSCRIPT_NODE_TYPE
{
    NODE_TYPE_INVALID = -1,
    NODE_TYPE_TIMER = 0,
    NODE_TYPE_COMMENT,
    NODE_TYPE_MEMORY,
    NODE_TYPE_FUNCTION,
    // if and conditions
    NODE_TYPE_IF,
    NODE_TYPE_SWITCH,
    NODE_TYPE_CONDITION,
};


/// basic structure of entity
class script_node
{
    public:

    /// node type
    VSCRIPT_NODE_TYPE type;

    script_node() 
    {
        /// constructor sets standard value to invalid value
        type = NODE_TYPE_INVALID;
        active = true;       
        node_name = "";
        node_comment = "";        
        position = vec(0,0,0);
        /// TODO
        position_changed = false;
    }

    ~script_node() {}

    /// members that every node must have
    vec position;
    bool active;
    bool selected;
    
    bool position_changed;

    /// the name of this node
    //char node_name[256];
    std::string node_name;

    /// the comment for this node
    /// use comments whenever possible
    //char node_comment[1024];
    std::string node_comment;

    /// whatever this node does will be implemented here
    virtual void run() = 0;

    // TODO: ...
    /*
    virtual void enable();
    virtual void disable();
    virtual void remove();
    virtual void insert();
    */

    /// we need Hanacks entity system at this point
    /// relation with other nodes?

    /// all parents
    std::vector<script_node*> incoming;
    /// all children
    std::vector<script_node*> outgoing;

    /// this will be called when the node gets activated
    void input() {}
    /// decide which children will be called
    void output() {}
};

#endif
