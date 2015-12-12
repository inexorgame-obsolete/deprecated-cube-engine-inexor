/// @file fl_comment.h
/// @author Johannes Schneider
/// @brief Comments will be rendered as text in 3D space. Use comments whenever its neccesary and useful!

/// .-------------------------------------------------------------------------------------------------.
/// | Comments                                                                                        |
/// |_________________________________________________________________________________________________|
/// |                                                                                                 |
/// | Use comments to remember decisions in your code and to explain difficult passages to others.    |
/// | Use comments whenever it is neccesary. Decide for yourself how to comment code!                 |
/// |_________________________________________________________________________________________________|
/// |                                                                                                 |
/// | This node type has no special members or methods because it is a comment and not part of        |
/// | the code itself.                                                                                |
/// ._________________________________________________________________________________________________.


#ifndef INEXOR_VSCRIPT_COMMENT_HEADER
#define INEXOR_VSCRIPT_COMMENT_HEADER

#include "inexor/engine/engine.h"
#include "inexor/flowgraph/node/fl_nodebase.h"

namespace inexor {
namespace vscript {

    class CCommentNode : public CScriptNode
    {
        public:

        CCommentNode(vec pos, const char* comment = "Hello Comment 1", const char* name = "CommentNode1");
        ~CCommentNode();

        /// comments are not part of the code itself
        /// so they do not run code or get notifyed or notify other nodes!
        /// still we have to implement these methods to make this class a valid
        /// child class of CScriptNode!
        void run()   {}
        void in()    {}
        void out()   {}
        void reset() {}
    };

};
};

#endif
