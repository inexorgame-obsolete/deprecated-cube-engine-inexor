/// @file fl_timer.h (flowgraph's timer implementation)
/// @author Johannes Schneider
/// @brief Comments will be placed in 3D space. Use comments whenever its neccesary!

/// .-------------------------------------------------------------------------------------------------.
/// | Comments                                                                                        |
/// |_________________________________________________________________________________________________|
/// |                                                                                                 |
/// | Use comments to remember decisions in your code and to explain it to others.                    |
/// | Use comments whenever it is neccesary. Decide for yourself how to comment code!.                |
/// |_________________________________________________________________________________________________|
/// |                                                                                                 |
/// | This node type has no special members or methods because it is a comment and not part of        |
/// | the code itself.                                                                                |
/// ._________________________________________________________________________________________________.
/// 

// include guard
#ifndef INEXOR_VSCRIPT_COMMENT_HEADER
#define INEXOR_VSCRIPT_COMMENT_HEADER

/// include basic node implementation and rendering engine
#include "inexor/engine/engine.h"
#include "inexor/flowgraph/node/fl_nodebase.h"

/// project's namespace protection
namespace inexor {
namespace vscript {


/// this class represents comment in 3D space
/// a comment can not run code at all
class comment_node : public script_node
{
    public:
    /// Please note: There is no standard constructor.

    /// overloaded standard constructor
    comment_node(vec pos, const char* comment, const char* name = "CommentName1");
    /// TODO: Is a destructor required?
    ~comment_node();

    /// comments are not part of the code itself
    /// so they do not run code or get notifyed or
    /// notify other nodes!
    void run() {}
    void in() {}
    void out() {}
    void reset() {}
};

/// end of namespace
};
};

#endif
