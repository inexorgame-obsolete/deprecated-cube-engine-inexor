#include "gtest/gtest.h"

#include "inexor/test/helpers.hpp"

#include "inexor/util/util.hpp"

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
    tchar("hello world this is patric", " ", "patric");
    tstr("asdxx",    "asd", "xx");
    tstr("", "sauhdsaiuhd", ""); // bugfix test!
    tstr("asdasd",   "asdasd", ""); // bugfix test!
  }
}

namespace {
  template<typename T> void t(T x, const char *cmp) {
    string res = to_string(x);
    expectEq(res, cmp);
  }

  test(to_string,works) {
    t("asd", "asd");
    t(string("asd"), "asd");
    t(22, "22");
  }
}

test(StringFormatter, works) {
  string s = fmt << "Hello World " << 22 << 'c';
  expectEq(s, "Hello World 22c");
}
