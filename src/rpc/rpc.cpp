#include <string>
#include <iostream>

#include "rpc/rpc.h"

#include "net/MCSocketServer.h"

using namespace std;
using namespace inexor::net;
using namespace inexor::util;

namespace inexor {
namespace rpc {

  // TODO: DEINIT
  MCServer *ipc_socket = NULL;
  InexorService *ipc_inexor_service = NULL;
  MCRpcServer *ipc_server = NULL;

  void rpc_init() {
#if defined(unix) || defined(__unix__) || defined(__unix)
    stringstream metap(ios::in | ios::out);
    //metap << "/tmp/inexor_ipc." << uuidgen() << ".socket";
    metap << "/tmp/inexor.socket";
    std::string path = metap.str();
    cerr << "[INFO] Listening for IPC connections on: "
      << path << endl;

    ipc_socket = new MCUnixServer(path);

    // TODO: Windows needs a fast (more secure) IPC transport
#else
    unsigned short port = 56732;
    cerr << "[INFO] Listening for IPC connections on port "
         << port << endl;

    // TODO: This should not require ipv4
    ipc_socket = new MCTcpServer(v4(), port);
#endif

    ipc_inexor_service = new InexorServiceImpl();
    ipc_server = new MCRpcServer(
        ipc_inexor_service, &ipc_socket->broadcast());
  }

  void rpc_tick() {
    if (!(ipc_socket && ipc_server)) return;
    ipc_socket->accept_all();
    ipc_server->ProcessAllCalls();
  }

  void rpc_destroy() {
    delete ipc_server;
    delete ipc_inexor_service;
    delete ipc_socket;
  }
}
}
