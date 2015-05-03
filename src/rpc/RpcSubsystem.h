#ifndef INEXOR_RPC_RPC_SUBSYSTEM_HEADER
#define INEXOR_RPC_RPC_SUBSYSTEM_HEADER

// Convenience Header

#include "net/MCServer.h"

#include "rpc/inexor_service.pb.h"
#include "rpc/InexorServiceImpl.h"
#include "rpc/MCRpcServer.h"

#include "util/Subsystem.h"

namespace inexor {
namespace rpc {


class RpcSubsystem : public inexor::util::Subsystem {
public:

    /// The connection we maintain
    inexor::net::MCServer *socket = NULL;
    /// RPC Call Negotiation
    MCRpcServer *server = NULL;
    /// RPC Function Implementation
    InexorService *rpc_service = new InexorServiceImpl();

    RpcSubsystem();
    virtual ~RpcSubsystem();

    virtual void tick();
};


}
}

#endif
