#include <istream>
#include <iostream>

#include "inexor/net/MessageConnect.h"
#include "inexor/net/MCByteBuffer.h"

using namespace std;

namespace inexor {
namespace net {

  bytes MCByteBuffer::xchrbuf(int reading_, size_t size) {
    reading = reading_;
    buf_pt = 0;
    bytes xb(size);
    buf.swap(xb);
    return xb;
  }

  // TODO: Support systems using big endian
  // TODO: SUPPORT DISCONNECT
  bytes MCByteBuffer::Receive() {
    // Try to fill the current buffer
    buf_pt += read(&buf[buf_pt], buf.size()-buf_pt);

    // Not enough data available; try again later
    if (buf.size() != buf_pt) return bytes(0);

    if (reading == rSize) { // Got the size
      uint64_t *sz = (uint64_t*)&buf[0];

      if (*sz > max_len) { // Invalid: too long
        // TODO: We need some sort of error/logger
        // TODO: Error. Close stream here.
        std::cerr << "[Stream Chopper] Message out of "
          << "bounds (" << *sz << " bytes)" << std::endl;
        xchrbuf(rSize); // retry to read the size
      }

      xchrbuf(rMessage, *sz);
      return Receive(); // Try to read the payload NOW

    // Success! Return current buffer; prepare for reading size
    } else
      return xchrbuf(rSize);
  }

  void MCByteBuffer::Send(const bytes &dat) {
    uint64_t size = dat.size();
    write((byte*)&size, sizeof(uint64_t));
    write(&dat[0], size);
  }

}
}
