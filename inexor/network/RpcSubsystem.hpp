#pragma once

#include <memory>
#include <queue>

#include <grpc/grpc.h>
#include <grpc++/grpc++.h>

#include "inexor/util/Subsystem.hpp"
#include "inexor/util/Logging.hpp"
#include "inexor/network/RpcServer.hpp"

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
    RpcServer<MSG_TYPE, ASYNC_SERVICE_TYPE> *serv = nullptr;
public:
    RpcSubsystem() { }

    ~RpcSubsystem()
    {
        spdlog::get("global")->info("RPC server stopped ({0})", serv->server_address);
        delete serv;
    }

    virtual void initialize(int argc, char **argv) override
    {
        if(argc < 2) return;
        std::string port = argv[1];
        std::string full_address = "0.0.0.0:"+ port;
        serv = new RpcServer<MSG_TYPE, ASYNC_SERVICE_TYPE>(full_address.c_str());
        spdlog::get("global")->info("RPC server listening on {0}", serv->server_address);
        set_on_change_functions();
        serv->block_until_initialized();
    }

    virtual void tick() override
    {
        if(serv) serv->process_queue();
    }
};


} // namespace inexor
} // namespace rpc

