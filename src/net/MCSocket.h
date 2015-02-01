#include <algorithm>
#include <cstddef>

#include <iostream>

#include <asio.hpp>

#include "net/MCByteBuffer.h"

#ifndef INEXOR_NET_IOSTREAM_MESSAGE_CONNECT_SOCKET_HEADER
#define INEXOR_NET_IOSTREAM_MESSAGE_CONNECT_SOCKET_HEADER

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

    typedef asio::io_service service;

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

    virtual size_t read(char *buf, size_t max) {
      size_t n = std::min(s.available(), max);
      if (n>0) s.read_some(asio::buffer(buf, n));
      return n;
    }

    virtual void write(char *buf, size_t len) {
      s.write_some(asio::buffer(buf,len));
    }
  };

  /**
   * MessageConnect via IPv4 or IPv6 TCP Socket.
   */
  class MCTcp : public MCSocket<asio::ip::tcp> {
  protected:
    typedef asio::ip::address address;

  public:
    /**
     * Create the connection from an IPv4 or IPv6 address
     * and the remote port number.
     *
     * TODO: Support generic endpoint initialization
     */
    MCTcp(const char *addr, unsigned short port) :
      MCSocket(address::from_string(addr), port) {}

    /**
     * Get the ASIO address.
     *
     * @return The address as represented by the ASIO lib.
     */
    address GetAddress() {
      return e.address();
    }
  };

#if defined(unix) || defined(__unix__) || defined(__unix)
  /**
   * MessageConnect via Unix Domain Socket.
   *
   * Initialize by MCUnix(const char* path)
   *
   * This is only available on unix systems
   *
   * TODO: Support initialization via std::string ?
   */
  typedef
    MCSocket<asio::local::stream_protocol>
    MCUnix;
#endif

}
}

#endif
