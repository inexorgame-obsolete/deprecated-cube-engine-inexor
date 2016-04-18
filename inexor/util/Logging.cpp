#include "inexor/util/Logging.hpp"

namespace inexor {
namespace util {

void initLoggers()
{
    // Create sinks
    std::vector<spdlog::sink_ptr> sinks;
    sinks.push_back(std::make_shared<spdlog::sinks::stdout_sink_st>());
    sinks.push_back(std::make_shared<inexor::util::InexorConsoleSink>());
    // sinks.push_back(std::make_shared<spdlog::sinks::ansicolor_sink>(std::make_shared<spdlog::sinks::stdout_sink_st>()));
    // sinks.push_back(std::make_shared<spdlog::sinks::ansicolor_sink>(std::make_shared<inexor::util::InexorConsoleSink>()));
    // sinks.push_back(std::make_shared<spdlog::sinks::daily_file_sink_st>("logfile", "txt", 23, 59));

    // Create loggers
    auto global = std::make_shared<spdlog::logger>("global", begin(sinks), end(sinks));
    auto chat = std::make_shared<spdlog::logger>("chat", begin(sinks), end(sinks));
    auto gameplay = std::make_shared<spdlog::logger>("gameplay", begin(sinks), end(sinks));

    // Register loggers to make them accessible globally
    spdlog::register_logger(global);
    spdlog::register_logger(chat);
    spdlog::register_logger(gameplay);
}

}
}
