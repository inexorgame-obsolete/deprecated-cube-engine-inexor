/// @file fl_timer.h (flowgraph's timer implementation)
/// @author Johannes Schneider
/// @brief Timers will be called every [n] miliseconds

// include guard
#ifndef INEXOR_VSCRIPT_COMMENT_HEADER
#define INEXOR_VSCRIPT_COMMENT_HEADER

/// include basic node implementation and rendering engine
#include "inexor/flowgraph/node/fl_nodebase.h"
#include "inexor/engine/engine.h"

/// project's namespace protection
namespace inexor {
namespace vscript {


/// this class represents comment in 3D space
/// a comment can not run code at all
class comment_node : public script_node
{
    public:

    /// overloaded standard constructor
    comment_node(vec pos, char* comment)
    {
        type = NODE_TYPE_COMMENT;
        position = pos;
        node_comment.copy(comment, strlen(comment));
        node_name.copy(comment, strlen(comment));
    }

    /// destructor has nothing to do (yet)
    ~comment_node() {}

    /// implementation of run
    /// there is no code a comment could run :)
    void run() {}
};

};
};

#endif
