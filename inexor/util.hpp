#ifndef INEXOR_UTIL_UTIL_HEADER
#define INEXOR_UTIL_UTIL_HEADER

#include <string>
#include <memory>
#include "inexor/util/StringFormatter.hpp"

namespace inexor {
namespace util {

  /// Convert stuff to a string.
  ///
  /// This works for anything that has the ostream <<
  /// operator defined.
  ///
  /// This internally simply uses the StringFormatter
  template<typename T> std::string to_string(T x) {
    return fmt << x;
  }

  /// Moving dynamic cast for unique_ptr
  ///
  /// If successful, the given pointer will be released and
  /// moved into the returned pointer with the new type.
  ///
  /// If the cast fails, the returned pointer will contain
  /// nullptr and the input pointer will be unmodified.
  template<typename To, typename From>
  std::unique_ptr<To> dynamic_pointer_cast(std::unique_ptr<From> &&f) noexcept {
    To *tp = dynamic_cast<To*>(f.get());
    if (tp != nullptr) f.release();
    return std::unique_ptr<To>{ tp };
  }

  /// Split a string and get the last component.
  ///
  /// Example:
  ///
  /// split_find_last("hello world this is patric", ' ')
  /// => "patric"
  ///
  /// TODO: Use the boost tokenize lib.
  ///
  /// @tparam T The type of the separator: Anything that
  ///           std::string::find_last_of would take (at
  ///           least char and string)
  /// @param s The String to split
  /// @param sep The char/string/... to separate s by
  /// @return The last element of s separated by sep
  ///
  template<typename T>
  std::string split_find_last(const std::string &s, T sep__) {

    std::string sep = to_string(sep__);

    size_t pos = s.rfind(sep);
    if (pos == std::string::npos) return s;

    pos += sep.size();
    if (pos == s.length()) return "";

    return s.substr(pos);
  }

/// Create a function alias
///
/// THX:
/// https://stackoverflow.com/questions/9864125/c11-how-to-alias-a-function
///
/// @param orig Name of the original functon
/// @param alias Name of the new alias function
#define INEXOR_FUNCTION_ALIAS(alias, orig)                 \
    template <typename... Args>                            \
    auto alias (Args&&... args)                            \
      -> decltype( orig(std::forward<Args>(args)...)) {    \
        return orig(std::forward<Args>(args)...);          \
    }

/// INEXOR_ATTR_UNUSED: Prevent the compiler from optimizing
/// variables that are never used away.
/// Useful, when all the interesting logic happens on the
/// assignment right side or in the
/// constructors/destructors.
///
#if defined(__GNUC__) && !defined(COMPILER_ICC)
    #define INEXOR_ATTR_UNUSED __attribute__ ((unused))
#else
    #define INEXOR_ATTR_UNUSED
#endif

}
}

#endif
