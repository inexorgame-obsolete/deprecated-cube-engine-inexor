#ifndef INEXOR_NET_MC_BYTE_BUFFER_HEADER
#define INEXOR_NET_MC_BYTE_BUFFER_HEADER

#include <vector>
#include <cstdint>
#include <cstddef>
#include <limits>

namespace inexor {
namespace net {

  /// MessageConnect wrapper for low lever read and write;
  /// subclasses provide non-blocking read/write function, we
  /// do the buffering.
  class MCByteBuffer : public MessageConnect {
  protected:
    /// Buffer storing the input
    /// TODO: Use some sort of buffer builder?
    bytes buf;

    /// Write pointer within buf
    uint64_t buf_pt = 0;

    const static int rSize = false;
    const static int rMessage = true;
    /// Indicates what we are currently reading:
    /// rSize -> The size of the message
    /// rMessage -> Got the size; reading the message itself.
    int reading;

    /// Slightly messy helper for transitioning between
    /// rSize and rMessage.
    ///
    /// Allocate a new buffer, save to buf and return the
    /// current buf.
    /// This also sets the buffer pointer (buf_pt) to 0.
    ///
    /// @param reading_ The new reading state to set
    /// @param size The new size of the buffer to allocate
    /// @return The current buf
    bytes xchrbuf(int reading_, size_t size=8);

  public:
    MCByteBuffer() {
      xchrbuf(rSize);
    }

    // Override
    virtual bytes Receive();
    // Override
    virtual void Send(const bytes &dat);

    /// Low level function to read some bytes.
    ///
    /// Read up to max bytes from the underlying transport
    /// into the buffer.
    ///
    /// This function never blocks.
    /// This function must be implemented by subclasses.
    ///
    /// Don't call this from outside. This is only exposed
    /// for the tests (TODO: Find some other way)
    ///
    /// @param buf The buffer to read into
    /// @param max The maximum number of bytes to read
    /// @return The number of bytes actually red
    virtual size_t read(byte *buf, size_t max) = 0;

    /// Low level function to write some bytes.
    ///
    /// Writes all the given bytes to the underlying
    /// transport.
    ///
    /// This function never blocks.
    /// This function does not buffer data!
    /// This function must be implemented by subclasses.
    ///
    /// Don't call this from outside. This is only exposed
    /// for the tests (TODO: Find some other way)
    ///
    /// @param buf The data to write
    /// @param len The number of bytes to write
    virtual void write(const byte *buf, size_t len) = 0;
  };

}
}

#endif
