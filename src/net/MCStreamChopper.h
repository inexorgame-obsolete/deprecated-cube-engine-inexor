#ifndef INEXOR_NET_MCSTREAMCHOPPER_HEADER
#define INEXOR_NET_MCSTREAMCHOPPER_HEADER

#include <stdexcept>
#include <iostream>

#include "net/MCByteBuffer.h"

namespace inexor {
namespace net {

  /// A MessageConnect with an basic_iostream as backend
  ///
  /// This just provides a very simple wrapper for
  /// MCByteBuffer that just redirects reads/writes to the
  /// associated streams.
  class MCStreamChopper : public MCByteBuffer {
  protected:

    /// @see In()
    std::istream *recv;
    /// @see Out()
    std::ostream *send;
    /// @see InOut()
    std::iostream *recv_send = NULL;

  public:

    /// Initialize both IN and OUT from the same IOStream.
    ///
    /// @param s The stream to read from and write to.
    MCStreamChopper(std::iostream *s)
        : recv(s), send(s), recv_send(s) {}

    /// Initialize recv/send from separate streams.
    ///
    /// recv/send may be NULL; if they are, Send resp. Receive
    /// might throw an error though.
    ///
    /// @param _recv The stream to read from
    /// @param _send The stream to write to
    MCStreamChopper(std::ostream *_send, std::istream *_recv)
        : recv(_recv), send(_send) {}

    virtual size_t read(byte *buf, size_t max) {
      if (!recv) throw std:: logic_error("This MCStreamChopper"
          " does not support receiving/reading data.");
      return recv->readsome((char*)buf, max);
    }

    virtual void write(byte *buf, size_t len) {
      if (!send) throw std::logic_error("This MCStreamChopper"
          " does not support sending/writing data.");
      send->write((char*)buf, len);
    }

    virtual bool supportSend() { return send; }
    virtual bool supportReceive() { return recv; }

    /// The stream we're reading from. If we're using
    /// a single, full duplex IOstream as backend, this will
    /// be the same as In and InOut
    std::istream* RecvStream() { return recv; }

    /// The stream we're writing to. If we're using
    /// a single, full duplex IOstream as backend, this will
    /// be the same as In and InOut
    std::ostream* SendStream() { return send; }

    /// If we're writing and reading on the same basic_iostream,
    /// this is the same as In() and Out()!
    /// Otherwise, this is NULL.
    std::iostream* SendRecvStream() { return recv_send; }
  };

}
}

#endif
