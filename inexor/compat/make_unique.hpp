// Make a unique ptr without using new;
//
// Will be standard in C++14; supported by boost but only
// from 1.56 (ubuntu provides 1.55)

#pragma once

// TODO: Use Boost implementation

#include <memory>
#include <utility>

namespace inexor {
namespace compat {

// https://stackoverflow.com/questions/17902405/how-to-implement-make-unique-function-in-c11
template<typename T, typename... Args>
std::unique_ptr<T> make_unique(Args&&... args) {
    return std::unique_ptr<T>(new T(std::forward<Args>(args)...));
}

}
}
