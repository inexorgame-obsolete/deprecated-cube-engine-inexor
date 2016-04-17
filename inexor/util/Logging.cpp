#include "inexor/util/Logging.hpp"

namespace inexor {
namespace util {

void InexorConsoleHandler::handle(const el::LogDispatchData* handlePtr)
{
    // NEVER LOG ANYTHING HERE!
    int type = 0;

    // Convert loggers and levels to legacy conline types:
    switch (handlePtr->logMessage()->level())
    {
        default:
        case el::Level::Info:
            type = 1<<0;
            break;
        case el::Level::Warning:
            type = 1<<1;
            break;
        case el::Level::Error:
            type = 1<<2;
            break;
        case el::Level::Debug:
            type = 1<<3;
            break;
    }
    conline(type, handlePtr->logMessage()->message().c_str());
    // For the new UI logging system we will probably need to pass loggerid as well.
}

void initLoggers()
{
    auto global = spdlog::stdout_logger_st("global");
    auto chat = spdlog::stdout_logger_st("chat");
    auto gameplay = spdlog::stdout_logger_st("gameplay");
}

}
}
