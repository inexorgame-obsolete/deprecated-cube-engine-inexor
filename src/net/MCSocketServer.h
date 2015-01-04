#ifndef SB_IPC_MC_SOCKET_SERVER_HEADER
#define SB_IPC_MC_SOCKET_SERVER_HEADER

#include <list>
#include <string>
#include <iostream>

#include <cstdint>
#include <cstdio>

#include <boost/asio.hpp>

#include "net/MessageConnect.h"
#include "net/MCHub.h"
#include "net/MCServer.h"
#include "net/StreamChopper.h"

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

    typedef
      boost::asio::basic_socket_acceptor< protocol >
      acceptor;
    typedef
      boost::asio::basic_socket_iostream< protocol >
      stream;
    typedef typename protocol::endpoint endpoint;
    typedef boost::asio::io_service service;

    service srv;
    endpoint end;
    acceptor ack;

    typedef std::list<stream> streamv;
    typedef typename streamv::iterator streamitr;
    std::list<stream> streams; // auto destruct

  protected:
    virtual MessageConnect* getNextStream() {
      streamitr s = streams.emplace(streams.end());
      boost::system::error_code er;

      ack.accept(*s->rdbuf(), er);
      
      if (er == boost::asio::error::basic_errors::try_again) {
        streams.erase(s);
        return NULL;
      } else if (er) {
        streams.erase(s);
        throw boost::system::system_error(er,
            "Can not accept connection");
      }

      std::cerr << "[INFO] New connection" << std::endl;
      
      return new StreamChopper(*s);
    }

  public:
    template <typename... T>
    MCSocketServer(T... x) : end(x...), ack(srv, end) {
      ack.non_blocking(true);
    }
  };

  // TODO: This belongs somewhere else
  extern boost::asio::ip::tcp v4();
  extern boost::asio::ip::tcp v6();

  /**
   * MCServer that listens on TCPv4/TCPv6.
   *
   * Initialize with
   *   MCTcpServer(boost::asio::ip::tcp protocol, unsigned short port)
   *   where protocol is one of v4() or v6().
   *
   * TODO: Support listening on specific interface.
   * TODO: Support authentification via file permissions.
   */
  typedef
    MCSocketServer< boost::asio::ip::tcp >
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
    public MCSocketServer< boost::asio::local::stream_protocol > {

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
