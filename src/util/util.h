#ifndef INEXOR_UTIL_UTIL_HEADER
#define INEXOR_UTIL_UTIL_HEADER

#include <string>

namespace inexor {
namespace util {

  template <typename T> inline void f_delete(T* x) {
    delete x;
  }

  extern std::string uuidgen();
}
}

#endif
