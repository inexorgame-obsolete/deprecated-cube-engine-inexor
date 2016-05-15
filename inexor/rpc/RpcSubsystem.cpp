

#include <grpc++/grpc++.h>


#include <chrono>
#include <iostream>
#include <memory>
#include <random>
#include <string>
#include <thread>

#include <grpc/grpc.h>
#include <grpc++/channel.h>
#include <grpc++/client_context.h>
#include <grpc++/create_channel.h>
#include <grpc++/security/credentials.h>

#include "inexor/rpc/RpcSubsystem.hpp"
#include "inexor/util/Logging.hpp"

#include "inexor/rpc/inexor_service.grpc.pb.h"

#include <moodycamel/concurrentqueue.h>

using grpc::Channel;
using grpc::ClientContext;
using grpc::ClientReader;
using grpc::ClientReaderWriter;
using grpc::ClientWriter;
using grpc::Server;
using grpc::ServerBuilder;
using grpc::ServerContext;
using grpc::ServerReader;
using grpc::ServerAsyncReaderWriter;
using grpc::ServerWriter;
using grpc::Status;
using grpc::CompletionQueue;
using grpc::ServerCompletionQueue;
using routeguide::Point;
using routeguide::RouteNote;
using routeguide::RouteGuide;
using std::chrono::system_clock;

moodycamel::ConcurrentQueue<std::string> writerqueue; // Something gets pushed on this when we changed value. Gets handled by serverthread.
moodycamel::ConcurrentQueue<std::string> readerqueue; // Something gets pushed on this when a value has arrived. Gets handled by Subsystem::tick();

/// Holding state, getting returned from completionqueue. Either reads or writes something in the stream.
class CallFunctor
{
    enum TYPE { TYPE_READER, TYPE_WRITER};
    TYPE type;

public:



    /// Creates a new instance of CallFunctor
    void setbusy()
    {

    }

    void sendmessage()
    {
        type = TYPE_WRITER;
    }

    void readmessage()
    {
        type = TYPE_READER;
    }

    void proceed()
    {
        if()
    }
};


void RunServer()
{

    std::thread t([]
    {
        std::string server_address("0.0.0.0:50051");

        RouteGuide::AsyncService service;

        ServerBuilder builder;
        builder.AddListeningPort(server_address, grpc::InsecureServerCredentials());
        builder.RegisterService(&service);

        std::unique_ptr<ServerCompletionQueue> scq = builder.AddCompletionQueue();

        std::unique_ptr<Server> server(builder.BuildAndStart());
        spdlog::get("global")->info() << "Server listening on " << server_address;
        server->Wait();
    }
    );
    t.detach();
}

//////// Client

Point MakePoint(long latitude, long longitude)
{
    Point p;
    p.set_latitude(latitude);
    p.set_longitude(longitude);
    return p;
}

RouteNote MakeRouteNote(const std::string& message, long latitude, long longitude)
{
    RouteNote n;
    n.set_msg(message);
    n.mutable_location()->CopyFrom(MakePoint(latitude, longitude));
    return n;
}

class RouteGuideClient
{
private:

    std::unique_ptr<RouteGuide::Stub> stub_;

public:
    RouteGuideClient(std::shared_ptr<Channel> channel)
        : stub_(RouteGuide::NewStub(channel)) { }

    void RouteChat()
    {
        ClientContext context;

        std::shared_ptr<ClientReaderWriter<RouteNote, RouteNote> > stream(stub_->RouteChat(&context));

        std::thread writer([stream]()
        {
            std::vector<RouteNote> notes{
                MakeRouteNote("First message", 0, 0),
                MakeRouteNote("Second message", 0, 1),
                MakeRouteNote("Third message", 1, 0),
                MakeRouteNote("Fourth message", 0, 0) };
            for (const RouteNote& note : notes) {
                spdlog::get("global")->info() << "Sending message " << note.msg() << " at " << note.location().latitude() << ", " << note.location().longitude();
                stream->Write(note);
            }
            stream->WritesDone();
        });

        RouteNote server_note;
        while (stream->Read(&server_note)) {
            spdlog::get("global")->info() << "Got message " << server_note.msg() << " at " << server_note.location().latitude() << ", " << server_note.location().longitude();
        }
        writer.join();
        Status status = stream->Finish();
        if (!status.ok()) {
            spdlog::get("global")->info() << "RouteChat rpc failed.";
        }
    }
};

void clientrpc()
{
    RouteGuideClient guide(grpc::CreateChannel("localhost:50051", grpc::InsecureChannelCredentials()));

    guide.RouteChat();
}


//struct changedvar
//{
//    /// Points to the var which needs to be updated.
//    void *pointer;
//    /// one of t
//    int datatype;
//    bool hasfunctionattached;
//    void *cb_function; // function which gets executed
//
//    union {
//        const char *str;
//        int 
//    };
//
//};
//void receivemessage()
//{
//    const char *inputpath; // /inputname
//    lookuptree("")
//}
//
//void otherthread()
//{
//
//}
//
//void onchangelistener()
//{
//    enque(variablename, value);
//}
//
//void mainthread
//{
//
//
//}

