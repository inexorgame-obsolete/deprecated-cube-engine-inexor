#pragma once

#include "inexor/network/SharedOptions.hpp"

// SKIP_FUNCTION_MACROS identifies all uppercase, single line macros without semicolon behind it.
#ifdef  GLUEGEN_PASS

/// This function is used so we have the SharedOptions in the AST somewhere when parsing.
inline bool function_args_dummy(const char *name, SharedOption a) { return true; }


/// We want people to discard the SharedOptions if there are none.
/// So they can write SharedFunc(quit) instead of SharedFunc(quit,)
/// https://stackoverflow.com/questions/3046889/optional-parameters-with-c-macros is used.
#define SharedFunc_1_ARGS(name, options) static bool __function_dummy_##name = function_args_dummy(#name, options)
#define SharedFunc_2_ARGS(name) static SharedOption __func_options_dummy_##name; static bool __function_dummy_##name = function_args_dummy(#name, __func_options_dummy_##name)

#define GET_3RD_ARG(arg1, arg2, arg3, ...) arg3
#define SharedFunc_MACRO_CHOOSER(...) \
    GET_3RD_ARG(__VA_ARGS__, SharedFunc_1_ARGS, SharedFunc_2_ARGS, )

#define SharedFunc(...) SharedFunc_MACRO_CHOOSER(__VA_ARGS__)(__VA_ARGS__)

#else
#define SharedFunc(name, ...)
#endif


