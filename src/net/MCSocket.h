#include <asio.hpp>

#ifndef INEXOR_NET_IOSTREAM_MESSAGE_CONNECT_SOCKET_HEADER
#define INEXOR_NET_IOSTREAM_MESSAGE_CONNECT_SOCKET_HEADER

namespace inexor {
namespace net {

  // TODO: Write URL handlers

  /**
   * Client for a MCSocketServer.
   *
   * Generic template for opening ASIO socket based
   * connections.
   *
   * The actual connection is maintained by the
   * StreamChopper code.
   * This class merely opens a connection as an ASIO
   * iostream and passes that down to StreamChopper.
   */
  template <typename protocol>
  class MCSocket : public StreamChopper {
  protected:

    typedef
      asio::basic_socket_iostream< protocol >
      stream;

    typedef
      typename protocol::endpoint
      endpoint;

    stream s;
    endpoint e;

  public:
    template<typename... T>
    MCSocket(T... x) : StreamChopper(s) {
      e = endpoint(x...);
      s.connect(e);
    }

    virtual ~MCSocket() {}
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
