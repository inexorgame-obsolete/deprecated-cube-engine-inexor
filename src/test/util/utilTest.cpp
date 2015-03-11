#include "gtest/gtest.h"

#include "test/helpers.h"

#include "util/util.h"

using namespace std;
using namespace inexor::util;

// testing split_find_last
namespace {
  typedef const char* cstr;

  template<typename T>
  void ttype(cstr s, T sep, cstr exp) {
    string a = split_find_last<T>(string(s), sep),
           b = string(exp);
    expectEq(a, b) << "Expected split_find_last('" << s
      << "', '" << sep << "') to return '" << exp
      << "', but it returned '" << a << "'";
  }

  void tstr(cstr s, cstr sep, cstr exp) {
    ttype<string>(s, string(sep), exp);
    ttype<cstr>(s, sep, exp);
  }

  void tchar(cstr s, cstr sep, cstr exp) {
    ttype<char>(s, sep[0], exp);
    tstr(s, sep, exp);
  }

  test(split_find_last, Splits) {
    tchar("1.2.3.4", ".", "4");
    tchar("a     x", " ", "x");
    tchar("",        ".", "");
    tchar("asdf",    ".", "asdf");
    tchar(".asdf",   ".", "asdf");
    tchar(".asdf.",  ".", "");
    tchar("",        "",  "");
    tchar("hello",   "",  "hello");
    tstr("asdxx",    "asd", "xx");
    tstr("asdasd",   "asdasd", "");
  }
}
