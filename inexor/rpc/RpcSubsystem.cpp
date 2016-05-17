

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
#include <moodycamel/blockingconcurrentqueue.h>

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
using inexor::tree::ChangedValue;
using inexor::tree::TreeService;


struct changedvar
{
    ///// Points to the var which needs to be updated.
    //SharedVar *pointer;
    ///// one of t
    //int datatype;
    //bool hasfunctionattached;
    //void *cb_function; // function which gets executed

    //union {
    //    const char *str;
    //    int 
    //};

};

//void findoneoffield(inexor::tree::Value val)
//{
//    const std::string path = val.GetTypeName();
//    val.GetDescriptor()->FindFieldByName(path);
//}



//struct writereq
//{
//    std::string path;
//    union {
//        const char *str;
//        int intval;
//        float floatval;
//    };
//    enum {VALUE_STR, VALUE_INT, VALUE_FLOAT} valuetype;
//};
moodycamel::ConcurrentQueue<std::string> writerrequestqueue; // Something gets pushed on this when we changed value. Gets handled by serverthread.
moodycamel::ConcurrentQueue<std::string> readerrequestqueue; // Something gets pushed on this when a value has arrived. Gets handled by Subsystem::tick();

void testserverwriter()
{
    //writereq req;
    //req.path = "inexor/tree/fullscreen";
    //req.intval = 1;
    //req.valuetype = writereq::VALUE_INT;
    writerrequestqueue.enqueue("inexor/tree/fullscreen");
}


ChangedValue MakeChangedValue(const char *path)
{
    ChangedValue c;
    c.set_path(path);
    return c;
}

/// Either a reading or writing request
struct CallInstance
{
    enum TYPES {READER, WRITER} type;

    bool isbusy = false;                    // only filled when request was write: workaround for grpc behavior to only allow one write at a time. 
    ChangedValue change;                    // the read will fill this on completion, the write filled it for reference when requesting the async write.

    ServerAsyncReaderWriter<ChangedValue, ChangedValue> *stream;

    CallInstance(TYPES type_, ServerAsyncReaderWriter<ChangedValue, ChangedValue> *stream_) : type(type_), stream(stream_) { }

    void startreading()
    {
        stream->Read(&change, (void *)this);
    }

    void startwrite(std::string &str) // todo const
    {
        change = MakeChangedValue(str.c_str());
        stream->Write(change, (void *)this);
    }
};

void RunServer()
{

    std::thread t([]
    {
        std::string server_address("0.0.0.0:50051");

        ServerBuilder builder;
        TreeService::AsyncService service;
        ServerContext context;
        ServerAsyncReaderWriter<ChangedValue, ChangedValue> stream(&context);

        builder.AddListeningPort(server_address, grpc::InsecureServerCredentials());
        builder.RegisterService(&service);

        // The completion queue (where notifications of the succcess of a network commands get retrieved).
        std::unique_ptr<ServerCompletionQueue> cq = builder.AddCompletionQueue();

        std::unique_ptr<Server> server = builder.BuildAndStart();
        spdlog::get("global")->info() << "Server listening on " << server_address;


        CallInstance *write = new CallInstance(CallInstance::WRITER, &stream);
        CallInstance *read  = new CallInstance(CallInstance::READER, &stream);

        /// Wait for the client to connect
        service.RequestSynchronize(&context, &stream, cq.get(), cq.get(), (void *)1);
        void *tag;
        bool succeed=false;
        cq->Next(&tag, &succeed);
        /// 

        read->startreading();
        std::vector<std::string> servnotes{
            "First servermsg",
            "Second servermsg",
            "Third servermsg",
            "Fourth servermsg"
        };
        int i = 0, j = 0;
        while(true)
        {
            std::string itemtosend;
            if(!write->isbusy && 
                i < 4) 
             //   writerrequestqueue.try_dequeue(itemtosend))
            {

                write->isbusy = true;
                write->startwrite(
                    servnotes[i]);
                    //itemtosend);
                i++;
            }

            void *tag;
            bool succeed=false;
            if(!cq->Next(&tag, &succeed))
            {
                spdlog::get("global")->debug() << "SSHIIT";
            }
            else
            if(tag != (void *)2)
            {
                CallInstance *completed = static_cast<CallInstance*>(tag);

                if(completed->type == CallInstance::WRITER) {
                    completed->isbusy = false;
                    j++;
                    if(j >= 4)
                    {
                        Status status;
                        //stream.Finish(status, (void *)2);
                    }
                }
                else
                {
                    readerrequestqueue.enqueue(completed->change.path());
                    // void *pointertosharedvar = Lookupinthetree(path);
                    // 
                    read->startreading(); // request new read
                }
            }
            else break;

        }
    }
    );
    t.detach();
}

//////// Client



class RouteGuideClient
{
private:

    std::unique_ptr<TreeService::Stub> stub_;
    ClientContext context;

public:
    std::shared_ptr<ClientReaderWriter<ChangedValue, ChangedValue> > stream;
    RouteGuideClient(std::shared_ptr<Channel> channel)
        : stub_(TreeService::NewStub(channel)), stream(stub_->Synchronize(&context))
    {
    }

    void RouteChat()
    {
        std::thread writer([this]()
        {
            std::vector<ChangedValue> notes{
                MakeChangedValue("First message"),
                MakeChangedValue("Second message"),
                MakeChangedValue("Third message"),
                MakeChangedValue("Fourth message")
            };
            for (const ChangedValue& note : notes) {
                spdlog::get("global")->info() << "Sending message " << note.path();
                stream->Write(note);
            }

            stream->WritesDone();
        });
        ChangedValue new_value;
        while (stream->Read(&new_value))
        {
            spdlog::get("global")->info() << "Got message " << new_value.path();
        }
        writer.join();
        //Status status = stream->Finish();
        //if (!status.ok()) {
        //    spdlog::get("global")->info() << "RouteChat rpc failed.";
        //}
    }
};

void clientrpc()
{
    RouteGuideClient *guide = new RouteGuideClient(grpc::CreateChannel("localhost:50051", grpc::InsecureChannelCredentials()));

    guide->RouteChat();
}




