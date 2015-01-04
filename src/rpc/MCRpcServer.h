#ifndef INEXOR_RPC_MCRPCSERVER_HEADER
#define INEXOR_RPC_MCRPCSERVER_HEADER

#include <google/protobuf/service.h>
#include <google/protobuf/descriptor.h>

#include <cstdbool>
#include <cstddef>
#include <cstdint>

#include "net/MessageConnect.h"

namespace inexor {
namespace rpc {

  /**
   * Rpc Server backed by a MessageConnect.
   *
   * The only thing you need to do is calling
   * ProcessAllCalls() or ProcessOneCall(), this should
   * automatically call the correct method in the service
   * object and then send the message right back.
   *
   * This implementation expects messages on the
   * MessageConnect. Those messages must be serialized
   * ServiceCall protobufs.
   * Return values are also encoded, serialized with the
   * ServiceCall and sent via the message connect.
   *
   * TODO: Implement the Closure (callback) and the
   *       RpcController
   */
  class MCRpcServer {
  private:
    typedef google::protobuf::Service Service;
    typedef inexor::net::MessageConnect MessageConnect;

    MessageConnect *mc = NULL;
    Service *service = NULL;

  public:
    /**
     * Create a new MCRpcServer.
     *
     * @param service_ The service to serve.
     * @param mc_ The message connect to use for receiving
     *   calls and sending return values.
     */
    MCRpcServer(Service *service_, MessageConnect *mc_)
        : mc(mc_), service(service_) {}

    /**
     * Process all calls to be processed.
     *
     * This calls ProcessOneCall() as long as it processes
     * calls.
     *
     * TODO: Limit/Timeout!
     *
     * @return The number of calls processed.
     */
    uint ProcessAllCalls();

    /**
     * Receive one call if available and execute the
     * associated code.
     *
     * @return Whether a call had been made.
     */
    bool ProcessOneCall();
  };

}
}

#endif
