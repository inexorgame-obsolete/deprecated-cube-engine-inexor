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

  // Split a string and get the last component.
  //
  // Example:
  //
  // split_find_last("hello world this is patric", ' ')
  // => "patric"
  //
  // TODO: Generalize; provide slicing iterator for
  // iterating bidirectionally through a list; provide
  // a converter to a std::list<string>
  // TODO: Generalize; make work on any sequence
  //
  // @tparam T The type of the separator: Anything that
  //           std::string::find_last_of would take (at
  //           least char and string)
  // @param s The String to split
  // @param sep The char/string/... to separate s by
  // @return The last element of s separated by sep
  //
  template<typename T>
  std::string split_find_last(const std::string &s, T sep,
          std::string::size_type pos=std::string::npos ) {

    std::string::size_type sep_pos, tok_pos;

    sep_pos = s.find_last_of(sep);
    tok_pos = sep_pos == std::string::npos ? 0 : sep_pos+1;

    // TODO: Slice, do not copy.
    return s.substr(tok_pos);
  }
}
}

#endif
