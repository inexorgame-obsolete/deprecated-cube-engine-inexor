#ifndef INEXOR_NET_MESSAGE_CONNECT_HEADER
#define INEXOR_NET_MESSAGE_CONNECT_HEADER

#include <vector>
#include <iostream>
#include <exception>
#include <utility>

#include <cstring>

namespace inexor {
namespace net {

  typedef unsigned char     byte;
  typedef std::vector<byte> bytes;

  /**
   * Abstract interface for a reliable, connection
   * connection that transmits Messages (Datagrams).
   *
   * For reasons of convenience this is aliased as MC.
   */
  class MessageConnect {
  public:
    typedef std::pair<bytes, MessageConnect*> bytes_on_channel;

    const static size_t default_max_len = 16<<10; //16kib
    size_t max_len = default_max_len;

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
     * @throws logic_error If receiving on this MessageConnect
     *         is not supported.
     * @see supportsReceive
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
     * @throws logic_error If receiving on this MessageConnect
     *         is not supported.
     * @see supportsReceive
     * @see MCHub
     */
    virtual bytes_on_channel ReceiveChannel() {
      return std::make_pair(Receive(), this);
    }

    /**
     * Send a Message.
     *
     * @param dat The message
     * @throws logic_error If sending on this MessageConnect
     *         is not supported.
     * @see supportsSend
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
     * @throws logic_error If sending on this MessageConnect
     *         is not supported.
     * @see supportsSend
     */
    virtual void Send(void *dat, size_t len) {
      bytes d(len);
      memcpy(&d[0], dat, len); // TODO: This is shit and very inefficient
      Send(d);
    }

    /// Check whether this message connect supports sending.
    ///
    /// If not overwritten, this always returns true.
    virtual bool supportSend() { return true; }

    /// Check whether this message connect supports
    /// receiving.
    ///
    /// If not overwritten, this always returns true.
    virtual bool supportReceive() { return true; }
    
    virtual ~MessageConnect() {}
  };

  /**
   * Alias for MessageConnect.
   */
  typedef MessageConnect MC;
}
}

#endif
