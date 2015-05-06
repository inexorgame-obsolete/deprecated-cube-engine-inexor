#ifndef INEXOR_UTIL_INEXOR_EXCEPTION_HEADER
#define INEXOR_UTIL_INEXOR_EXCEPTION_HEADER

#include <exception>
#include <string>
#include "util/StringFormatter.h"

/// Visual studio does not support noexcept;
/// INEXOR_NOEXCEPT only enable noexcept on platforms that
/// support it
#ifndef _MSC_VER
    #define INEXOR_NOEXCEPT noexcept
#else
    #define INEXOR_NOEXCEPT
#endif

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
public:
    const char *_what;

    /// Default constructor
    ///
    /// Initializes what() with a generic message.
    InexorException() INEXOR_NOEXCEPT {
        _what = "Some problem occurred in the inexor code. Dunno what.";
    }

    /// Initialize this exception with a custom error
    /// message
    /// @param s The error message
    InexorException(const char *s) INEXOR_NOEXCEPT {
        _what = s;
    }

    /// Initialize this exception with a custom error
    /// message
    ///
    /// @param s The error message
    InexorException(std::string &s) INEXOR_NOEXCEPT {
        _what = s.c_str();
    }

    /// Initialize this exception with a custom error
    /// message in a string
    /// @param s The error message
    InexorException(const InexorException &e) 
          INEXOR_NOEXCEPT : std::exception(e) {
        _what = e._what;
    }

    /// The name of this exception class.
    virtual const char* clazz() {
        return "InexorException";
    }

    /// Generates an error message appropriate for logging
    virtual const char* message() {
        std::string s =
          inexor::util::fmt << clazz() << ": " << what();
        return s.c_str();
    }

    virtual const char* what() const INEXOR_NOEXCEPT {
        return _what;
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
#define EXCEPTION(name, base, __what   )                    \
    class name : public base {                              \
    public:                                                 \
        name () INEXOR_NOEXCEPT : base ( __what ) {}        \
        name (const char *s) INEXOR_NOEXCEPT : base (s) {}  \
        name (std::string &s) INEXOR_NOEXCEPT : base (s) {} \
        name (const name &e) INEXOR_NOEXCEPT : base (e) {}  \
        virtual const char* clazz() INEXOR_NOEXCEPT {       \
            return #name ;                                  \
        }                                                   \
    }

/// Like EXCEPTION but uses InexorException as base, so no
/// need to specify one manually
#define IEXCEPTION(name, __what) \
    EXCEPTION(name, ::inexor::util::InexorException, __what)

}
}

#endif
