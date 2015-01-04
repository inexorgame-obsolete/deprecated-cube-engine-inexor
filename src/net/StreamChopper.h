#ifndef INEXOR_NET_IOSTREAM_MESSAGE_CONNECT_HEADER
#define INEXOR_NET_IOSTREAM_MESSAGE_CONNECT_HEADER

#include <istream>
#include <vector>
#include <cstdint>
#include <limits>

#include <thread>

#include "util/LockingQueue.h"

namespace inexor {
namespace net {

  /**
   * MessageConnect backed by an std::iostream.
   *
   * NOTE: iostream does not support asynchronous
   *   (non-blocking) IO, so this simulates async IO by
   *   starting a separate thread and sending messages via
   *   queue to the main thread.
   */
  class StreamChopper : public MessageConnect {
  protected:
    /** The Stream we're communication via */
    std::iostream *str;

    /** 
     * Buffer for storing input
     * TODO: Is this necessary? IOstreams are buffered.
     * TODO: Maybe use stringstream?
     */
    std::vector<char> buf;

    /** Write pointer withing buf */
    uint64_t buf_pt = 0; 

    /** 
     * Two states: Either we are reading a size or a full
     * message.
     */
    bool have_size = false;

    /** Thread that runs reader_thread() */
    std::thread *thr;
    /** This is where reader_thread() passes messages */
    inexor::util::LockingQueue<bytes> thr_sync;

    /** Synchronous receive; used by reader_thread */
    bytes reader_thread_reveive();
    /** Thread to simulate async IO */
    void reader_thread();

  public:
    // At first we want to load the uint64_t, hence the
    // 8 byte buffer
    StreamChopper(std::iostream &s_) : buf(8) {
      str = &s_;
      thr = new std::thread(&StreamChopper::reader_thread, this);
    }

    virtual ~StreamChopper() {
      // TODO: Stop thread
      delete thr;
    }

    // Override
    virtual MC::bytes Receive();
    // Override
    virtual void Send(MC::bytes &dat);
  };

}
}

#endif
