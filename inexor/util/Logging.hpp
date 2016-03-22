#ifndef INEXOR_UTIL_LOGGING
#define INEXOR_UTIL_LOGGING

#define ELPP_THREAD_SAFE
// #define ELPP_UNICODE
#define ELPP_FORCE_USE_STD_THREAD
// #define ELPP_DEFAULT_LOG_FILE
#define ELPP_DISABLE_DEFAULT_CRASH_HANDLING
#define ELPP_WINSOCK2

#include <easylogging++.h>
#include <iomanip>

/// Function which displayes console text ingame.
extern void conline(int type, const char *sf);

namespace inexor {
namespace util {

    // ANSI Console colors: everything behind it will be in that particular color.
    #define COL_GREEN   "\x1b[38;2;64;255;128m" // \x1b[38;2; is the ANSI escape sequence for 24bit foreground color, then the RGB values follow (+ closing 'm').
    #define COL_BLUE    "\x1b[38;2;96;160;255m"
    #define COL_YELLOW  "\x1b[38;2;255;192;64m"
    #define COL_RED     "\x1b[38;2;255;64;64m"
    #define COL_GREY    "\x1b[38;2;128;128;128m"
    #define COL_MAGENTA "\x1b[38;2;192;64;192m"
    #define COL_ORANGE  "\x1b[38;2;255;128;0m"
    #define COL_WHITE   "\x1b[38;2;255;255;255m"

    /// Wrapper for easylogger for telling it to call our callback every time something gets logged (so we can display it ingame).
    class InexorConsoleHandler : public el::LogDispatchCallback {
        public:
            InexorConsoleHandler();
            void handle(const el::LogDispatchData* handlePtr);
    };

    /// Helper class to allow the writing of std::cout << embraced("I should be inside curly brackets", "{", "}");
    struct embraced
    {
        const char *_text,
                   *_leading,  // e.g. "{"
                   *_trailing; // e.g. "}"

        embraced(const char *text, const char *leading, const char *trailing) : _text(text), _leading(leading), _trailing(trailing) {}

        /// Construct a std::string from this class.
        operator std::string() const
        {
            std::string quotedStr = _leading;
            quotedStr += _text;
            quotedStr += _trailing;
            return quotedStr;
        }

        /// Pass this class directly into a stream.
        friend std::ostream &operator<< (std::ostream & ostr, const embraced & q)
        {
            ostr << q._leading << q._text << q._trailing;
            return ostr;
        }
    };

    /// A simple helper class to allow you writing inexor::util::quoted(string) which automatically adds quotation marks.
    /// When either constructing an std::string from it or << it into a stream (e.g. LOG()).
    struct quoted : embraced
    {
        quoted(const char *text) : embraced(text, "\"", "\"") {}
    };
}
}

#endif
