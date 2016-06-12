

#include "inexor/rpc/RpcSubsystem.hpp"
#include "inexor/util/Logging.hpp"
#include <memory>
#include <string>

#include <grpc++/grpc++.h>

#include "inexor/rpc/inexor_service.grpc.pb.h"
#include "inexor/rpc/inexor_service.pb.h"


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

using grpc::Channel;
using grpc::ClientContext;
using grpc::Status;
using helloworld::HelloRequest;
using helloworld::HelloReply;
using helloworld::Greeter;

class GreeterClient {
public:
    GreeterClient(std::shared_ptr<Channel> channel)
        : stub_(Greeter::NewStub(channel)) {}

    // Assambles the client's payload, sends it and presents the response back
    // from the server.
    std::string SayHello(const std::string& user) {
        // Data we are sending to the server.
        HelloRequest request;
        request.set_name(user);

        // Container for the data we expect from the server.
        HelloReply reply;

        // Context for the client. It could be used to convey extra information to
        // the server and/or tweak certain RPC behaviors.
        ClientContext context;

        // The actual RPC.
        Status status = stub_->SayHello(&context, request, &reply);

        // Act upon its status.
        if (status.ok()) {
            return reply.message();
        }
        else {
            return "RPC failed";
        }
    }

private:
    std::unique_ptr<Greeter::Stub> stub_;
};

void testclientrpc()
{
    // Instantiate the client. It requires a channel, out of which the actual RPCs
    // are created. This channel models a connection to an endpoint (in this case,
    // localhost at port 50051). We indicate that the channel isn't authenticated
    // (use of InsecureChannelCredentials()).
    GreeterClient greeter(grpc::CreateChannel("localhost:50051", grpc::InsecureChannelCredentials()));
    std::string user("world");
    std::string reply = greeter.SayHello(user);
    spdlog::get("global")->info() << "Greeter received: " << reply;

}

}
}
