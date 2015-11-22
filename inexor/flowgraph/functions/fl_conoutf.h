/// @file fl_conoutf.h
/// @author Johannes Schneider
/// @brief This game engine function prints a text to the game console (locally)
/// 
/// TODO: We need a good interface for function parameters here!
/// 
/// .-------------------------------------------------------------------------------------------------.
/// | conoutf(CON_DEBUG, [text with symbols], [...] );                                                |
/// |_________________________________________________________________________________________________|
/// |                                                                                                 |
/// | Prints a text to the game console (local).                                                      |
/// |                                                                                                 |
/// ._________________________________________________________________________________________________.
/// 


#ifndef INEXOR_VSCRIPT_CONOUTF_HEADER
#define INEXOR_VSCRIPT_CONOUTF_HEADER

#include "inexor/engine/engine.h"
#include "inexor/flowgraph/node/fl_nodebase.h"
#include "inexor/flowgraph/functions/fl_functionbase.h"

namespace inexor {
namespace vscript {

    class CFunctionConoutfNode : public CScriptNode
    {
        protected:
    
        /// output
        std::string param_text_output;
        std::string raw_text_input;

        public:

        CFunctionConoutfNode(vec pos, const char* raw_text);
        ~CFunctionConoutfNode();

        /// TODO: format
        void format_output();

        void in();
        void run();
        void out();
        void reset();
    };

/// end of namespaces
};
};

#endif
