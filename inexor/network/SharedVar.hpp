#pragma once

#include <algorithm>

#include <boost/signals2.hpp>

#include "inexor/network/SharedOptions.hpp"
namespace inexor {
namespace rpc {

/// SharedVar wrapper for primitive/immutable objects
///
/// This first and foremost is a wrapper around stuff.
/// We provide * and -> operators to work with the value and
/// define a cast operator that casts to the contained
/// value.
/// It best works with primitive or non mutable values, as
/// changes to the value can not be detected.
///
/// The cast operator can make some problems, when the
/// compiler can not figure out what to use and you might
/// see some giant error cascades.
/// In these cases, try using the value itself
/// (`*observ_instance`) or using an explicit cast.
///
/// SharedVar provides a special assignment operator: If
/// that is called, it first calls the onChange event with
/// the old and the new value.
/// Only afterwards the new value is assigned.
///
/// The value of the variable inside SharedVar is undefined
/// while the listeners are called;
///
/// During the event, do not change the value of the
/// variable (that would create an recursive event),
/// or the parameters.
///
/// ## Example
///
/// ```
/// SharedVar<int> oi = 22;
///
/// oi.onChange.connect([] (const int &a, const int &b)
///     {
///         spdlog::get("global")->info("hey we changed! (old: {} new: {}", a, b);
///     }
/// );
///
/// void main() {
///     oi = 33;
///     oi += 22;
/// }
/// ```
template<typename T>
class SharedVar {
private:
    typedef SharedVar<T> TMe;

    template<typename... A>
    using signal = boost::signals2::signal<A...>;

    T value;
public:

    /// Event that is fired when a new value is assigned;
    ///
    /// This does however not fire, when the value is merely
    /// modified
    ///
    /// params: old value, new value
    signal<void(const T&, const T&)> onChange;

    // Access

    T& operator *() { return value; }
    const T& operator *() const { return value; }
    T* operator ->() { return &value; }

    // Note: Let's see whether this causes too much problems
    operator T&() { return value; }

    // Proxies

//   explicit SharedVar() : value() {}

    template<typename... Args>
    explicit SharedVar(Args&&... args, SharedOption)
        : value(std::forward<Args>(args)...) {}

    explicit SharedVar(const SharedVar<T> &otr) : value(otr.value) {}
    explicit SharedVar(T &otr) : value(otr) {}
    explicit SharedVar(T &&otr) : value(otr) {} // Shuu TODO we need to reenable this!
 //   explicit SharedVar(T otr, SharedOption) : value(otr) {}
    explicit SharedVar(T &otr, SharedOption) : value(otr) {}
    explicit SharedVar(T &&otr, SharedOption) : value(otr) {}

    // Avoid ambiguity when observing a string
    T operator= (const char *c) {
        T nu(c);
        onChange(value, nu);
        return value = nu;
    }

    T operator =(const T &otr) {
        onChange(value, otr);
        value = otr;
        return value;
    }

    T operator =(T &&otr) {
        onChange(value, otr);
        value = std::move(otr);
        return value;
    }

    // TODO: Put all the operator macro invocations into
    // own file so we reuse them in the test.

    // TODO: Component assignment operators (+= -= ..)
    // TODO: Performance: return by reference for operators

#define UNR(op)                  \
    T operator op (int) {        \
        T old = value;           \
        T ret = value op;        \
        onChange(old, value);    \
        return ret;              \
    }

    UNR(++);
    UNR(--);

#undef UNR

#define UNL(op)                  \
    T operator op () {           \
        T old = value;           \
        T ret = op value;        \
        onChange(old, value);    \
        return ret;              \
    }

    UNL(++);
    UNL(--);

#undef UNL


#define ASGN(op)                       \
    template<typename O>               \
    T operator op ## =(const O &otr) { \
        T old = value;                 \
        T ret = value op ## = otr;     \
        onChange(old, value);          \
        return ret;                    \
    }

    ASGN(+);
    ASGN(-);
    ASGN(*);
    ASGN(/);
    ASGN(%);
    ASGN(&);
    ASGN(|);
    ASGN(^);
    ASGN(<<);
    ASGN(>>);

#undef ASGN


    // This is for seriliazation usage only, to not get caught in endless loop when receiving new values
    // TODO find another way (since other watchers wont be notified as well anymore)
    void setnosync(const char *c)
    {
        value = c;
    }

    void setnosync(const T &otr)
    {
        value = otr;
    }

    void setnosync(T &&otr)
    {
        value = std::move(otr);
    }

    void sync()
    {
        onChange(value, value);
    }
};

// Output Operator

template<typename T>
std::ostream& operator<<(std::ostream& os, const SharedVar<T> &x) {
    os << *x;
    return os;
}


// Specializations for min/max (otherwise they are causing
// frequent problems)
// TODO: Get rid of ::min, ::max; define these for std::*

template<typename T>
const T& min(const inexor::rpc::SharedVar<T> &a, const T &b) {
    return std::min(*a, b);
}
template<typename T>
const T& min(const T &a, const inexor::rpc::SharedVar<T> &b) {
    return std::min(a, *b);
}
template<typename T>
const T& min(const inexor::rpc::SharedVar<T> &a, const inexor::rpc::SharedVar<T> &b)
{
    return std::min(*a, *b);
}

template<typename T>
const T& max(const inexor::rpc::SharedVar<T> &a, const T &b) {
    return std::max(*a, b);
}
template<typename T>
const T& max(const T &a, const inexor::rpc::SharedVar<T> &b) {
    return std::max(a, *b);
}
template<typename T>
const T& max(const inexor::rpc::SharedVar<T> &a, const inexor::rpc::SharedVar<T> &b)
{
    return std::max(*a, *b);
}

} // ns inexor::rpc
} // ns inexor

// Import into global namespace.
using inexor::rpc::SharedVar;

