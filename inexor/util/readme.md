# inexor::util

Util is catchall module for any *generic* functionality that
is to small to get it's own module.

Just include `util/util.h` to pull everything.

At the moment we provide StringFormatter – a one line
method of formatting strings:

  ```
  string s = fmt << "Hello this is " << "a string" << 42 << eosl;
  ```

# Requires

* C++11
* stdc++
