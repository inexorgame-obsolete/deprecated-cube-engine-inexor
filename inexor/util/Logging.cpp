#include "inexor/util/Logging.hpp"

namespace inexor {
namespace util {

InexorConsoleHandler::InexorConsoleHandler()
{
    el::Loggers::getLogger("console");
}

void InexorConsoleHandler::handle(const el::LogDispatchData* handlePtr)
{
    // NEVER LOG ANYTHING HERE!
    int type = 0;
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
}

}
}
