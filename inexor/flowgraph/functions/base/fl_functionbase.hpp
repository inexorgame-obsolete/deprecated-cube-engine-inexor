/// @file fl_functionbase.hpp
/// @author Johannes Schneider
/// @brief every visual script function that is linked 
/// with the game engine will inherit from this base class.

#ifndef INEXOR_VSCRIPT_FUNCTION_BASE_HEADER
#define INEXOR_VSCRIPT_FUNCTION_BASE_HEADER

namespace inexor {
namespace vscript {

    /// @brief every visual script function node
    /// will be specified as one of the following functions.
    enum INEXOR_VSCRIPT_FUNCTIONS
    {
        INEXOR_VSCRIPT_FUNCTION_CONOUTF,
        INEXOR_VSCRIPT_FUNCTION_PLAYSOUND,
        // TODO: enlarge the list of linked functions!
        // TODO: enlarge list automaticly?
    };

    class CFunctionBase
    {
        public:

            CFunctionBase();
            ~CFunctionBase();

            // TODO: implement parameters and a return value!
    };

};
};

#endif
