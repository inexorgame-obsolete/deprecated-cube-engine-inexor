#include <string>

#ifndef INEXOR_UTIL_UTIL_HEADER
#define INEXOR_UTIL_UTIL_HEADER

namespace inexor {
namespace util {
  // The delete operator as a function.
  //
  // Calls delete on any pointer given.
  //
  // @tparam T The type of pointer to delete
  // @param x The pointer to delete
  template <typename T> inline void f_delete(T* x) {
    delete x;
  }

  /// Convert stuff to a string.
  ///
  /// This works for anything that has the ostream <<
  /// operator defined.
  ///
  /// This internally simply uses the StringFormatter
  template<typename T> std::string to_string(T x) {
    return fmt << x;
  }

  // Split a string and get the last component.
  //
  // Example:
  //
  // split_find_last("hello world this is patric", ' ')
  // => "patric"
  //
  // TODO: Use the boost tokenize lib.
  //
  // @tparam T The type of the separator: Anything that
  //           std::string::find_last_of would take (at
  //           least char and string)
  // @param s The String to split
  // @param sep The char/string/... to separate s by
  // @return The last element of s separated by sep
  //
  template<typename T>
  std::string split_find_last(const std::string &s, T sep__) {

    std::string sep = to_string(sep__);

    size_t pos = s.rfind(sep);
    if (pos == std::string::npos) return s;

    pos += sep.size();
    if (pos == s.length()) return "";

    return s.substr(pos);
  }
}
}

#endif
