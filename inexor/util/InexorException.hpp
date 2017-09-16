#pragma once

#include <exception>
#include <string>
#include "inexor/util/StringFormatter.hpp"

namespace inexor {
namespace util {

/// Basic exception type for use in inexor
///
/// This type (1) provides an exception type that excludes
/// all exceptions from outside inexor and (2) provides
/// the ability to set the reason (`what`) when throwing
/// the exception.
///
/// @see IEXCEPTION This macro allows you to subclass
///      InexorException on the fly.
///
/// TODO: STACK TRACE
/// TODO: Allow setting the message on the fly with the <<
///       operator
class InexorException : public std::exception {
    std::string what_ = "Some problem occurred in the "
        "inexor code. Dunno what.";
public:

    /// Default constructor
    ///
    /// Initializes what() with a generic message.
    InexorException() {}

    /// Initialize this exception with a custom error
    /// message
    /// @param s The error message
    InexorException(const char *s) : what_(s) {}

    /// Initialize this exception with a custom error
    /// message
    ///
    /// @param s The error message
    InexorException(const std::string &s) : what_(s) {}

    /// Initialize this exception with a custom error
    /// message in a string
    /// @param e The error message
    InexorException(const InexorException &e)
        : std::exception(e), what_(e.what_){}

    /// The name of this exception class.
    virtual const char* clazz() {
        return "InexorException";
    }

    /// Generates an error message appropriate for logging
    virtual std::string message() {
        return inexor::util::fmt << clazz() << ": " << what_;
    }

    virtual const char* what() const noexcept {
        return what_.c_str();
    }
};

/// Create exceptions on the fly
///
///   EXCEPTION(IdioticException,
///       InexorException, "Well, this is silly.");
///   ...
///   IdioticException a, b("Pow pow!");
///   a.what(); // => "Well, this is silly."
///   b.what(); // => "Pow, pow!"
///
/// @param name The name of the new exception class
/// @param base The name of the base exception class to extend
/// @param __what The default error message, when none is
///               set on the fly
#define EXCEPTION(name, base, __what   )                   \
    class name : public base {                             \
    public:                                                \
        name() : base(__what) {}                           \
        name(const char *s) : base(s) {}                   \
        name(const std::string &s) : base(s) {}            \
        name(const InexorException &e) : base(e) {}        \
        virtual const char* clazz() noexcept {      \
            return #name ;                                 \
        }                                                  \
    }

/// Like EXCEPTION but uses InexorException as base, so no
/// need to specify one manually
#define IEXCEPTION(name, __what) \
    EXCEPTION(name, ::inexor::util::InexorException, __what)

}
}
