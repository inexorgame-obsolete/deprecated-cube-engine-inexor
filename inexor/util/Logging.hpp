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

}
}

#endif
