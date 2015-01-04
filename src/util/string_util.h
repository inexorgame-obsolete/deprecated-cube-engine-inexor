#ifndef INEXOR_UTIL_STRING_UTIL_HEADER
#define INEXOR_UTIL_STRING_UTIL_HEADER

#include <string>
#include <list>

#include <stddef.h>

namespace inexor {
namespace util {

  // TODO: Generalize; provide slicing iterator for
  // iterating bidirectionally through a list; provide
  // a converter to a std::list<string>
  
  // TODO: Generalize; make work on any sequence

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
