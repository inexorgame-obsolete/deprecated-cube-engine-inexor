#ifndef INEXOR_RPC_RPC_SB_COMPAT_HEADER
#define INEXOR_RPC_RPC_SB_COMPAT_HEADER

// This file avoids exposing anything but the functions to
// be called from master, because inexor dares do
// declare stuff like string in a global namespace.

namespace inexor {
namespace rpc {

  /**
   * Sets up the RPC subsystem
   *
   * TODO: This should be a class!
   */
  extern void rpc_init();
  /**
   * Update the rpc subsystem event loop.
   *
   * Accepts new IPC connections and processes all available
   * calls.
   *
   * Should be called once every frame or so.
   * Does nothing if rpc_init has not been called.
   */
  extern void rpc_tick();

  /**
   * Shut down the RPC subsystem.
   *
   * Frees all the resources allocated by rpc_init()
   * Does nothing if rpc_init has not been called.
   */
  extern void rpc_destroy();

}
}

#endif

