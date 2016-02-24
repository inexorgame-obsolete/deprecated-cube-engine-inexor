/// @file fl_functionbase.h
/// @author Johannes Schneider
/// @brief Every function that is linked with the game engine will inherit from this base class

#ifndef INEXOR_VSCRIPT_FUNCTION_BASE_HEADER
#define INEXOR_VSCRIPT_FUNCTION_BASE_HEADER


enum INEXOR_VSCRIPT_FUNCTIONS
{
    FUNCTION_CONOUTF,
    FUNCTION_PLAYSOUND,
};


namespace inexor {
namespace vscript {

    class CFunctionBase
    {
        public:

        CFunctionBase();
        ~CFunctionBase();

        // TODO: implement parameters and return value!
    };

};
};

#endif
