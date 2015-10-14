/// @file fl_functionbase.h
/// @author Johannes Schneider
/// @brief Every function of the game engine will inherit from this base class
/// 
/// .-------------------------------------------------------------------------------------------------.
/// | Base class for linked game engine functions                                                     |
/// |_________________________________________________________________________________________________|
/// |                                                                                                 |
/// | Many game engine functions should be accessible through the 3D Visual Scripting Enviroment.     |
/// | Every linked function inherits from this base class.                                            |
/// |                                                                                                 |
/// |                                                                                                 |
/// ._________________________________________________________________________________________________.
/// 

/// Include guard
#ifndef INEXOR_VSCRIPT_FUNCTION_BASE_HEADER
#define INEXOR_VSCRIPT_FUNCTION_BASE_HEADER

/// TODO: list more in-engine functions
enum INEXOR_VSCRIPT_FUNCTIONS
{
    FUNCTION_CONOUTF,
    FUNCTION_PLAYSOUND,
};


/// Inexor namespace protection
namespace inexor {
namespace vscript {

/// A basic function node
class function_base_node
{
    public:
    function_base_node();
    ~function_base_node();

    /// TODO: parameter manager
    /// TODO: return value(s)
};

/// end of namespace
};
};

#endif
