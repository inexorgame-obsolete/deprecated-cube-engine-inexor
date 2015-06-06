#ifndef INEXOR_RPC_RPC_SUBSYSTEM_HEADER
#define INEXOR_RPC_RPC_SUBSYSTEM_HEADER

// Convenience Header

#include <memory>

#include "inexor/net/MCServer.h"

#include "inexor/rpc/inexor_service.pb.h"
#include "inexor/rpc/InexorServiceImpl.h"
#include "inexor/rpc/MCRpcServer.h"

#include "inexor/util/Subsystem.h"

#include "inexor/compat/make_unique.h"

namespace inexor {
namespace rpc {

class RpcSubsystem : public inexor::util::Subsystem {
public:

    /// The connection we maintain
    std::unique_ptr<inexor::net::MCServer> socket;
    /// RPC Call Negotiation
    std::unique_ptr<MCRpcServer> server;
    /// RPC Function Implementation
    std::unique_ptr<InexorService> rpc_service =
        inexor::compat::make_unique<InexorServiceImpl>();

    RpcSubsystem();

    void tick();
};


}
}

#endif
