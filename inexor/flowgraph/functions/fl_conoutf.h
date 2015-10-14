/// @file fl_conoutf.h
/// @author Johannes Schneider
/// @brief This game engine function prints a text to the game console (local)
/// 
/// TODO: We need a good interface for function parameters here (CEF!)
/// 
/// .-------------------------------------------------------------------------------------------------.
/// | conoutf(CON_DEBUG, [text], [...] );                                                             |
/// |_________________________________________________________________________________________________|
/// |                                                                                                 |
/// | Prints a text to the game console (local).                                                      |
/// |                                                                                                 |
/// ._________________________________________________________________________________________________.
/// 


#ifndef INEXOR_VSCRIPT_CONOUTF_HEADER
#define INEXOR_VSCRIPT_CONOUTF_HEADER

/// Include base class
#include "inexor/flowgraph/node/fl_nodebase.h"
#include "inexor/flowgraph/functions/fl_functionbase.h"

/// conoutf implementation
#include "inexor/engine/engine.h"

/// Inexor 
namespace inexor {
namespace vscript {

/// Function
class function_conoutf_node : public script_node
{
    protected:
    
    /// output
    std::string param_text_output;
    std::string raw_text_input;

    public:

    /// constructor
    function_conoutf_node(vec pos, const char* raw_text);

    /// destructor
    ~function_conoutf_node();

    void in();
    void run();

    /// TODO: format
    void format_output();

    void out();
    /// TODO: ?
    void reset();

};

};
};

#endif
