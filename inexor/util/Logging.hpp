#ifndef INEXOR_UTIL_LOGGING
#define INEXOR_UTIL_LOGGING

#define ELPP_THREAD_SAFE
// #define ELPP_UNICODE
#define ELPP_FORCE_USE_STD_THREAD
// #define ELPP_DEFAULT_LOG_FILE
#define ELPP_DISABLE_DEFAULT_CRASH_HANDLING
#define ELPP_WINSOCK2

#include <easylogging++.h>

extern void conline(int type, const char *sf);

namespace inexor {
namespace util {

    // wrapper/callback für das logging-zeug der jedesmal conline( bei bestimmten verbositätsstufen aufruft

    // refactoring: conoutf existiert 2x: in server.cpp und in main.cpp -> nur noch 1x in logger.cpp

    // colors: conoutf

    class InexorConsoleHandler : public el::LogDispatchCallback {
        public:
            InexorConsoleHandler();
            void handle(const el::LogDispatchData* handlePtr);
    };


    /// A simple helper class to allow you writing inexor::util::quoted(string) which automatically adds quotation marks.
    /// When either constructing an std::string from it or << it into a stream (e.g. LOG()).
    struct quoted
    {
        const char * _text;
        quoted(const char * text) : _text(text) {}

        operator std::string() const
        {
            std::string quotedStr = "\"";
            quotedStr += _text;
            quotedStr += "\"";
            return quotedStr;
        }

        friend std::ostream &operator<< (std::ostream & ostr, const quoted & q)
        {
            ostr << "\"" << q._text << "\"";
            return ostr;
        }
    };
}
}

#endif
