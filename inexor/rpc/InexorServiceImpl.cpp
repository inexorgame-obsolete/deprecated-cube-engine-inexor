#if defined(__MINGW32__) && (defined(__X86__) || defined(_X86_) || defined(i386))
// Work around a mingw bug: Both intrin.h (included by
// SDL.h) and x86intrin.h (included by the stdlib) declare
// intrinsics. However the former one uses "extern C", while
// the latter one does not. Hence g++ complains about
// conflicting declarations
// The linkage for intrinsics doesn't matter, but at that
// stage the compiler doesn't know; so, to avoid compile
// errors we ensure that x86intrin.h is included with an
// `extern C` declaration.
//
// See:
// * https://sourceforge.net/tracker/index.php?func=detail&aid=3018394&group_id=202880&atid=983354
// * http://eigen.tuxfamily.org/bz/attachment.cgi?id=48&action=diff#a/Eigen/Core_sec2
// * http://eigen.tuxfamily.org/bz/show_bug.cgi?id=125
extern "C" {
#include <x86intrin.h>
}
#endif

#include <iostream>
#include "inexor/rpc/InexorServiceImpl.hpp"

// Legacy
#include "inexor/shared/cube.hpp"

using namespace google::protobuf;

namespace inexor {
namespace rpc {


//  void InexorServiceImpl::EvalCubescript(RpcController* ctrl,
//      const Cubescript* req, CubescriptResult* res,
//      Closure* done)
//  {
//
//#ifndef STANDALONE
//    //tagval *commandret;
//    ::executeret(req->code().c_str(), *commandret);
//    tagval &v = *commandret;
//    
//    switch (v.type) {
//      case VAL_STR:   res->set_s(v.getstr()); break;
//      case VAL_INT:   res->set_i(v.getint()); break;
//      case VAL_FLOAT: res->set_f(v.getfloat()); break;
//      case VAL_NULL:   break;
//      default:
//        std::cerr << "[ERROR] Invalid command return value!"
//                  << std::endl;
//        // TODO: Proper error handling
//    }
//#endif
//  
//    if (done)
//      done->Run();
//  }

}
}
