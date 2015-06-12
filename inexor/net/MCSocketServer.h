#ifndef SB_IPC_MC_SOCKET_SERVER_HEADER
#define SB_IPC_MC_SOCKET_SERVER_HEADER

#include <list>
#include <string>
#include <iostream>
#include <memory>

#include <cstdint>
#include <cstdio>

#include <asio.hpp>

#include "inexor/net/MessageConnect.h"
#include "inexor/net/MCServer.h"
#include "inexor/net/MCSocket.h"
#include "inexor/compat/make_unique.h"

namespace inexor {
namespace net {
  
  /**
   * Generic implementation for an ASIO based MCServer.
   *
   * This serves as basis for TCPv4/TCPv6/UNIX-SOCKET based
   * MCServers.
   */
  template <typename protocol>
  class MCSocketServer : public MCServer {
  protected:

    typedef asio::basic_socket_acceptor<protocol> acceptor;
    typedef typename protocol::endpoint endpoint;
    typedef asio::io_service service;

    typedef MCSocket<protocol> mcsoc;

    service srv;
    endpoint end;
    acceptor ack;

  protected:
    virtual std::unique_ptr<MessageConnect> getNextStream() {
      asio::error_code er;
      std::unique_ptr<mcsoc> s =
          inexor::compat::make_unique<mcsoc>(srv);

      ack.accept(s->Socket(), er);

      if (er == asio::error::basic_errors::try_again)
        return NULL;
      else if (er == asio::error::basic_errors::would_block) //caused by calling in mainloop
        return NULL;
      else if (er)
        throw asio::system_error(er, "Can not accept connection");

      std::cerr << "[INFO] New connection" << std::endl;
      // TODO: Add casting functions for unique_ptr
      return std::unique_ptr<MessageConnect>(s.release());
    }

  public:
    template <typename... T>
    MCSocketServer(T... x) : end(x...), ack(srv, end) {
      ack.non_blocking(true);
    }
  };

  // TODO: This belongs somewhere else
  extern asio::ip::tcp v4();
  extern asio::ip::tcp v6();

  /**
   * MCServer that listens on TCPv4/TCPv6.
   *
   * Initialize with
   *   MCTcpServer(asio::ip::tcp protocol, unsigned short port)
   *   where protocol is one of v4() or v6().
   *
   * TODO: Support listening on specific interface.
   * TODO: Support authentification via file permissions.
   */
  typedef
    MCSocketServer< asio::ip::tcp >
    MCTcpServer;

#if defined(unix) || defined(__unix__) || defined(__unix)
  /**
   * MCServer that listens on a Unix domain socket.
   *
   * Initialize with
   *   MCUnixServer(const char *path)
   *
   * TODO: Initialize with std::string path
   * TODO: Auto delete socket file
   */
  class MCUnixServer :
    public MCSocketServer< asio::local::stream_protocol > {

      std::string path;
  public:
    /**
     * Initialize a new UnixSocket server with a path
     *
     * @param path Path of the unix socket
     */
    MCUnixServer(const char *path_)
        : MCSocketServer( (remove(path_), path_) ),
          path(path_) {}

    /**
     * Initialize a new UnixSocket server with a path
     *
     * @param path Path of the unix socket
     */
    MCUnixServer(std::string &path_)
      : MCUnixServer(path_.c_str()) {}

    /**
     * Destroy this socket server
     *
     * Just deletes the socket link
     */
    virtual ~MCUnixServer() {
      remove(path.c_str());
    }
  };


#endif
  
}
}

#endif
