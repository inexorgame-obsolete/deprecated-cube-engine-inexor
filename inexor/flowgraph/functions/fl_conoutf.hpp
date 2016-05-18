/// @file fl_conoutf.h
/// @author Johannes Schneider
/// @brief Print a text message to the local game console

#ifndef INEXOR_VSCRIPT_CONOUTF_HEADER
#define INEXOR_VSCRIPT_CONOUTF_HEADER

#include "inexor/flowgraph/nodebase/fl_base.hpp"


namespace inexor {
namespace vscript {

    class CFunctionConoutfNode : public CScriptNode
    {
        protected:

            std::string param_text_output;
            std::string raw_text_input;

        public:

            CFunctionConoutfNode(vec pos, const char* raw_text);
            ~CFunctionConoutfNode();

            void format_output();

            void in();

            bool OnLinkAsChildNodeAttempt(CScriptNode* parent);
            bool OnLinkAsParentNodeAttempt(CScriptNode* child);
    };

};
};

#endif
