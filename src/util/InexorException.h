#ifndef INEXOR_UTIL_INEXOR_EXCEPTION_HEADER
#define INEXOR_UTIL_INEXOR_EXCEPTION_HEADER

#include <exception>
#include <string>

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
class InexorException : public std::exception {
public:
    const char *_what;

    /// Default constructor
    ///
    /// Initializes what() with a generic message.
    InexorException() noexcept {
        _what = "Some problem occurred in the inexor code. Dunno what.";
    }

    /// Initialize this exception with a custom error
    /// message
    /// @param s The error message
    InexorException(const char *s) noexcept {
        _what = s;
    }

    /// Initialize this exception with a custom error
    /// message
    ///
    /// @param s The error message
    InexorException(std::string &s) noexcept {
        _what = s.c_str();
    }

    /// Initialize this exception with a custom error
    /// message in a string
    /// @param s The error message
    InexorException(const InexorException &e) noexcept
          : std::exception(e) {
        _what = e._what;
    }

    virtual const char* what() const noexcept {
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
#define EXCEPTION(name, base, __what)                 \
    class name : base {                               \
    public:                                           \
        name () noexcept : base ( __what ) {}         \
        name (const char *s) noexcept : base (s) {}   \
        name (std::string &s) noexcept : base (s) {}  \
        name (const name &e) noexcept : base (e) {}   \
    }

/// Like EXCEPTION but uses InexorException as base, so no
/// need to specify one manually
#define IEXCEPTION(name, __what) \
    EXCEPTION(name, ::inexor::util::InexorException, __what)

}
}

#endif
