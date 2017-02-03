#pragma once

#include "inexor/rpc/SharedOptions.hpp"
#include "inexor/rpc/SharedVar.hpp"

using inexor::rpc::SharedVar;

#include "inexor/rpc/SharedClass.hpp"

// SKIP_FUNCTION_MACROS identifies all uppercase, single line macros without semicolon behind it.
#ifdef  GLUEGEN_PASS

  /// This function is used so we have the SharedOptions in the AST somewhere when parsing.
  inline bool function_args_dummy(const char *name, SharedOption a) { return true; }
#define SharedFunc(name, options) static bool __function_dummy_##name = function_args_dummy(#name, options)
#else
  #define SharedFunc(name, options)
#endif
