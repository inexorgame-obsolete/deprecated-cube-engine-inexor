#pragma once

#include <memory>
#include <queue>

#include <grpc/grpc.h>
#include <grpc++/grpc++.h>

#include "inexor/util/Subsystem.hpp"
#include "inexor/util/Logging.hpp"
#include "inexor/rpc/RpcServer.hpp"

namespace inexor {
namespace rpc {

// These functions need to be implemented by the Context Provider (acquiring this submodule):
extern void set_on_change_functions();
extern void send_all_vars();
extern const std::unordered_map<int64, void *> cppvar_pointer_map;
extern const std::unordered_map<int64, int> index_to_type_map;

template<typename MSG_TYPE, typename ASYNC_SERVICE_TYPE>
class RpcSubsystem : public inexor::util::Subsystem
{
    RpcServer<MSG_TYPE, ASYNC_SERVICE_TYPE> serv;
public:
    RpcSubsystem() : serv("0.0.0.0:50051")
    {
        spdlog::get("global")->info("RPC server listening on {0}", serv.server_address);
        set_on_change_functions();
    }

    void tick() override
    {
        serv.process_queue();
    }
};


} // namespace inexor
} // namespace rpc

