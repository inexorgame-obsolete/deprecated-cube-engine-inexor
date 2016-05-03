#ifndef INEXOR_RPC_INEXOR_SERVICE_IMPL_HEADER
#define INEXOR_RPC_INEXOR_SERVICE_IMPL_HEADER

#include <google/protobuf/service.h>
#include "inexor/rpc/inexor_service.pb.h"

namespace inexor {
namespace rpc {

  /**
   * Default implementation of the InexorService.
   *
   * @see inexor_service.proto
   
  class InexorServiceImpl : public InexorService_Stub {
    typedef google::protobuf::RpcController RpcController;
    typedef google::protobuf::Closure Closure;

  public:
    InexorServiceImpl() : InexorService_Stub(NULL) {}

    void EvalCubescript(RpcController* ctrl,
        const Cubescript* req, CubescriptResult* res,
        Closure* done);
  };
*/
}
}

#endif
