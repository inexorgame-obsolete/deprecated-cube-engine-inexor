#include "rpc/InexorServiceImpl.h"

#include <iostream>

// Legacy
#include "shared/cube.h"

using namespace google::protobuf;

namespace inexor {
namespace rpc {


  void InexorServiceImpl::EvalCubescript(RpcController* ctrl,
      const Cubescript* req, CubescriptResult* res,
      Closure* done) {

#ifndef STANDALONE
    tagval v;
    ::executeret(req->code().c_str(), v);

    switch (v.type) {
      case VAL_STR:   res->set_s(v.getstr()); break;
      case VAL_INT:   res->set_i(v.getint()); break;
      case VAL_FLOAT: res->set_f(v.getfloat()); break;
      case VAL_NULL:   break;
      default:
        std::cerr << "[ERROR] Invalid command return value!"
                  << std::endl;
        // TODO: Proper error handling
    }
#endif
  
    if (done)
      done->Run();
  }

}
}
