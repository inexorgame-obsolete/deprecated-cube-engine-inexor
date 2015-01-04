#ifndef INEXOR_NET_MESSAGE_CONNECT_HEADER
#define INEXOR_NET_MESSAGE_CONNECT_HEADER

#include <vector>
#include <iostream>
#include <exception>
#include <utility>

#include <cstring>

namespace inexor {
namespace net {

  /**
   * Abstract interface for a reliable, connection
   * connection that transmits Messages (Datagrams).
   *
   * For reasons of convenience this is aliased as MC.
   */
  class MessageConnect {
  public:
    // TODO: Use uchar
    // TODO: This should be called message
    typedef std::vector<char> bytes;
    typedef std::pair<bytes, MessageConnect*> bytes_on_channel;

    /**
     * Receive a Message.
     *
     * When not overridden, this calls ReceiveChannel() and
     * takes it's bytes `ReceiveChannel().first`.
     *
     * This is always non-blocking.
     *
     * @return The Message or an empty vector if no message
     *         is available.
     */
    virtual bytes Receive() {
      return ReceiveChannel().first;
    }

    /**
     * Receive a message get a specific MessageConnect* to
     * be used for returning messages.
     *
     * This is useful for scenarios in which
     * a MessageConnect acts as a server for Multiple
     * client MessageConnects.
     * In this case the MessageConnect given will normally
     * sort of representing the remote client.
     *
     * This is always non-blocking.
     *
     * @return A pair, with the first element being the
     *    Message received and the second elemnt being
     *    a MessageConnect* to be used for returning Messages.
     *
     *    If no message is available, the message will be an
     *    empty vector and the value of the MessageConnect*
     *    is undefined.
     * @see MCHub
     */
    virtual bytes_on_channel ReceiveChannel() {
      return std::make_pair(Receive(), this);
    }

    /**
     * Send a Message.
     *
     * @param dat The message
     */
    virtual void Send(bytes &dat) = 0;

    /**
     * Send a message contained in a plain memory.
     *
     * NOTE: This is currently slower that the vector<char>
     *       implementation.
     *
     * @param dat A pointer to the memory containing the message
     * @param len The length of the message
     */
    virtual void Send(void *dat, size_t len) {
      bytes d(len);
      memcpy(&d[0], dat, len); // TODO: This is shit and very inefficient
      Send(d);
    }
    
    virtual ~MessageConnect() {}
  };

  /**
   * Alias for MessageConnect.
   */
  typedef MessageConnect MC;
}
}

#endif
