/// @file fl_conoutf.hpp
/// @author Johannes Schneider
/// @brief links the game engine's conoutf function to Visual Scripting Enviroment

#ifndef INEXOR_VSCRIPT_CONOUTF_HEADER
#define INEXOR_VSCRIPT_CONOUTF_HEADER

#include "inexor/flowgraph/nodebase/fl_base.hpp"

namespace inexor {
namespace vscript {

    class CFunctionConoutfNode : public CScriptNode
    {
        protected:

            std::string console_text;

        public:

            CFunctionConoutfNode(vec pos, const char* text);
            ~CFunctionConoutfNode();
            
            void in();

            bool OnLinkAsChildNodeAttempt(CScriptNode* parent);
            bool OnLinkAsParentNodeAttempt(CScriptNode* child);
    };

};
};

#endif
