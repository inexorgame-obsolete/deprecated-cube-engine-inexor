/// @file fl_functionbase.hpp
/// @author Johannes Schneider
/// @brief every function that is linked with the game engine will inherit from this base class

// TODO: make use of the new tree interface to link functions automaticly

#ifndef INEXOR_VSCRIPT_FUNCTION_BASE_HEADER
#define INEXOR_VSCRIPT_FUNCTION_BASE_HEADER


enum INEXOR_VSCRIPT_FUNCTIONS
{
    INEXOR_VSCRIPT_FUNCTION_CONOUTF,
    INEXOR_VSCRIPT_FUNCTION_PLAYSOUND,
};


namespace inexor {
namespace vscript {

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
