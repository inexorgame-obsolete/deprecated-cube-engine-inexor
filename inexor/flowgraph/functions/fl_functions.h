/// @file fl_functions.h
/// @author Johannes Schneider
/// @brief Game engine functions such as conoutf(); will be linked to the Script System in this file
/// 
/// TODO: We need a good interface for function parameters here (CEF!)
/// 
/// .-------------------------------------------------------------------------------------------------.
/// | Functions                                                                                       |
/// |_________________________________________________________________________________________________|
/// |                                                                                                 |
/// | Many game engine functions should be accessible through the 3D Visual Scripting Enviroment.     |
/// | The following functions will be linked to the system:                                           |
/// |                                                                                                 |
/// | conoutf(CON_DEBUG, "text");       will print a static text to the game console (no params yet)  |
/// |                                                                                                 |
/// ._________________________________________________________________________________________________.
/// 

/// Please note: every function inherits from CFunctionBase (fl_functionbase.h)

/// @brief conoutf prints output to the game console (local player)
#include "inexor/flowgraph/functions/fl_conoutf.h"

/// @brief playsound simply plays a sound with standard parameters
#include "inexor/flowgraph/functions/fl_playsound.h"