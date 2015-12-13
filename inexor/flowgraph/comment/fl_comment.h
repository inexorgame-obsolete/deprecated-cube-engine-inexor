// @file fl_comment.h
// @author Johannes Schneider
// @brief Comments will be rendered as text in 3D space. Use comments whenever its neccesary and useful!

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
        void run()   {}
        void in()    {}
        void out()   {}
        void reset() {}
    };

};
};

#endif
