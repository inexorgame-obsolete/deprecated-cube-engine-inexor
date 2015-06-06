#ifndef INEXOR_NET_IOSTREAM_MESSAGE_CONNECT_SOCKET_HEADER
#define INEXOR_NET_IOSTREAM_MESSAGE_CONNECT_SOCKET_HEADER

#include <algorithm>
#include <cstddef>

#include <iostream>

#include <boost/asio.hpp>

#include "inexor/net/MCByteBuffer.h"

namespace inexor {
namespace net {


  /// Client for a MCSocketServer.
  ///
  /// Generic template for opening ASIO socket based
  /// connections.
  ///
  /// TODO: Write URL handlers
  template <typename protocol>
  class MCSocket : public MCByteBuffer {
  protected:
    typedef typename protocol::endpoint endpoint;
    typedef typename protocol::socket   socket;

    typedef boost::asio::io_service service;

    bool own_srv = false;
    service *srv;

    endpoint e;
    socket s;

  public:
    /// Default constructor with special service.
    /// Do something with socket()
    MCSocket(service &srv_) : srv(&srv_), s(*srv) {}

    /// Default constructor with fresh ASIO io service
    /// Do something with socket()
    MCSocket() : own_srv(true), srv(new service), s(*srv) {}

    /// Initialize with endpoint arguments and a service.
    template<typename... T>
    MCSocket(service &srv_, T... x) :
        srv(&srv_), e(x...), s(*srv, e) {}

    /// Initialize with endpoint arguments and a fresh io
    /// service.
    template<typename... T>
    MCSocket(T... x) : own_srv(true), srv(new service),
        e(x...), s(*srv, e) {}

    ~MCSocket() {
      if (own_srv) delete srv;
    }

    /// Get the endpoint attached to this
    endpoint& Endpoint() { return e; }

    /// Get the ASIO socket attached to this
    socket& Socket() { return s; }

    /// Get the ASIO io srvice of this
    service* Service() { return srv; }

    virtual size_t read(byte *buf, size_t max) {
      size_t n = std::min(s.available(), max);
      if (n>0) s.read_some(boost::asio::buffer(buf, n));
      return n;
    }

    virtual void write(const byte *buf, size_t len) {
      s.write_some(boost::asio::buffer(buf,len));
    }
  };

  /// MessageConnect via IPv4 or IPv6 TCP Socket.
  ///
  /// TODO: Support generic endpoint initialization
  class MCTcp : public MCSocket<boost::asio::ip::tcp> {
  protected:
    typedef boost::asio::ip::address address;

  public:
    /// Create the connection from an IPv4 or IPv6 address
    /// and the remote port number.
    ///
    /// A new ASIO service will be creates for this.
    MCTcp(const char *addr, unsigned short port) :
      MCSocket(address::from_string(addr), port) {}

    /// Create the connection from an IPv4 or IPv6 address
    /// and the remote port number in a specific service.
    MCTcp(service &srv, const char *addr, unsigned short port) :
      MCSocket(srv, address::from_string(addr), port) {}

    /// Create the connection from an IPv4 or IPv6 address
    /// and the remote port number in a specific service.
    ///
    /// A new ASIO service will be creates for this.
    MCTcp(std::string addr, unsigned short port) :
      MCTcp(addr.c_str(), port) {}

    /// Create the connection from an IPv4 or IPv6 address
    /// and the remote port number in a specific service.
    MCTcp(service &srv, std::string addr, unsigned short port) :
      MCTcp(srv, addr.c_str(), port) {}

    /// Get the ASIO address.
    ///
    /// @return The address as represented by the ASIO lib.
    address GetAddress() {
      return e.address();
    }
  };

#if defined(unix) || defined(__unix__) || defined(__unix)
  /// MessageConnect via Unix Domain Socket.
  ///
  /// This is only available on Unix systems.
  class MCUnix : MCSocket<boost::asio::local::stream_protocol> {
  protected:
    std::string path;

  public:

    /// Connect to the unix socket at path.
    MCUnix(const char *path_)
      : MCSocket(path_), path(path_) {}

    /// Connect to the unix socket at path with a specific
    /// ASIO service.
    MCUnix(service &srv, const char *path_) :
      MCSocket(srv, path_), path(path_) {}

    /// Connect to the unix socket at path.
    MCUnix(std::string path_)
      : MCSocket(path_.c_str()), path(path_) {}

    /// Connect to the unix socket at path with a specific
    /// ASIO service.
    MCUnix(service &srv, std::string path_)
      : MCSocket(srv, path_.c_str()), path(path_) {}

    /// Get the path of the underlying unix socket
    std::string Path() { return path; }
  };
#endif

}
}

#endif
