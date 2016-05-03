#include <string>
#include <iostream>

#include "inexor/rpc/RpcSubsystem.hpp"

using namespace std;
using namespace inexor::util;

SUBSYSTEM_REGISTER(rpc, inexor::rpc::RpcSubsystem);

namespace inexor {
namespace rpc {

RpcSubsystem::RpcSubsystem()
{
//#if defined(unix) || defined(__unix__) || defined(__unix)
//    string path = "/tmp/inexor.socket";
//    cerr << "[INFO] Listening for IPC connections on: "
//      << path << endl;
//
//    socket = inexor::compat::make_unique<MCUnixServer>(path);
//
//    // TODO: Windows needs a fast (more secure) IPC transport
//#else
//    unsigned short port = 56732;
//    cerr << "[INFO] Listening for IPC connections on port "
//          << port << endl;
//
//    // TODO: This should not require ipv4
//    socket = inexor::compat::make_unique<MCTcpServer>(v4(), port);
//#endif
//
//    server = inexor::compat::make_unique<MCRpcServer>(
//        rpc_service.get(), socket.get());
}

void RpcSubsystem::tick()
{
    //socket->accept_all();
    //server->ProcessAllCalls();
}

}
}
