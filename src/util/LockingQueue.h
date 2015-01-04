#ifndef INEXOR_UTIL_LOCKING_QUEUE_HEADEr
#define INEXOR_UTIL_LOCKING_QUEUE_HEADEr

#include <list>
#include <mutex>

namespace inexor {
namespace util {

  template<typename T>
  class LockingQueue {

    std::mutex mtx;
    std::list<T*> dat;

  public:
    virtual T* pop() {
      mtx.lock();
      T* x;
      if (dat.empty())
        x = NULL;
      else {
        x = dat.back();
        dat.pop_back();
      }
      mtx.unlock();
      return x;
    }

    virtual void push(T* x) {
      mtx.lock();
      dat.push_front(x);
      mtx.unlock();
    }
  };

}
}

#endif
