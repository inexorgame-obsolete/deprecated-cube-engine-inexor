#include <istream>
#include <iostream>


#include "net/MessageConnect.h"
#include "net/StreamChopper.h"

#include <unistd.h>

using namespace std;

namespace inexor {
namespace net {

  void StreamChopper::reader_thread() {
    MC::bytes r(0);
    while (true) {
      r = reader_thread_reveive();
      if (!r.empty()) {
        MC::bytes *got = new bytes(0);
        r.swap(*got);
        thr_sync.push(got);
      }
    }
  }

  // TODO: Support systems using big endian
  // TODO: SUPPORT DISCONNECT
  MC::bytes StreamChopper::reader_thread_reveive() {
    // TODO: Is this a good thing to do?
    str->clear();
    str->sync();

    // Try to fill the current buffer
    str->read(&buf[buf_pt], buf.size()-buf_pt);
    int no = str->gcount();
    buf_pt += no;

    // Not enough data available; try again later
    if (buf.size() != buf_pt)
      return vector<char>(0);

    // else: We do have enough data; use the buffer red in
    // some way and reset stuff for reading new data:w
    
    buf_pt = 0;

    // Got the size of the message; prepare buffer for
    // reading the big message and go into message reading
    // state
    if (!have_size) {
      have_size = true;
      uint64_t *sz = (uint64_t*)&buf[0];
      buf = vector<char>(*sz);
      return Receive(); // Try to read the payload NOW

    // The full message could be red; go into size reading
    // state, prepare buffer for reading the size and return
    // the current buffer
    } else {
      have_size = false;
      vector<char> x(8);
      buf.swap(x);
      return x;
    }
  }

  MC::bytes StreamChopper::Receive() {
    MC::bytes out(0);
    MC::bytes *got = thr_sync.pop();
    if (got != NULL) {
      out.swap(*got);
      delete got;
    }
    return out;
  }

  void StreamChopper::Send(MC::bytes &dat) {
    str->clear();

    uint64_t size = dat.size();
    str->write((char*)&size, sizeof(uint64_t));
    str->write(&dat[0], size);

    str->flush();
  }

}
}
