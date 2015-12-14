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

        CCommentNode(vec pos, const char* comment = "An example text for a comment.", const char* name = "CommentNode1");
        ~CCommentNode();

        // comments do nothing at all
        void run()   {}
        void in()    {}
        void out()   {}
        void reset() {}
    };

};
};

#endif
