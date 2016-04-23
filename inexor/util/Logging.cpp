#include "inexor/util/Logging.hpp"

namespace inexor {
namespace util {

void initLoggers()
{
    // Set async mode
    size_t q_size = 4096; //queue size must be power of 2
    spdlog::set_async_mode(q_size);

    // Create sinks
    std::vector<spdlog::sink_ptr> sinks;
    sinks.push_back(std::make_shared<spdlog::sinks::stdout_sink_st>());
    sinks.push_back(std::make_shared<inexor::util::InexorConsoleSink>());
    // sinks.push_back(std::make_shared<spdlog::sinks::daily_file_sink_st>("inexor", "log", 23, 59));
    sinks.push_back(std::make_shared<inexor::util::InexorCutAnsiCodesSink>(std::make_shared<spdlog::sinks::daily_file_sink_st>("inexor", "log", 23, 59)));

    // Create loggers
    auto global = std::make_shared<spdlog::logger>("global", begin(sinks), end(sinks));
    auto chat = std::make_shared<spdlog::logger>("chat", begin(sinks), end(sinks));
    auto gameplay = std::make_shared<spdlog::logger>("gameplay", begin(sinks), end(sinks));
    auto edit = std::make_shared<spdlog::logger>("edit", begin(sinks), end(sinks));
    auto frag_involved = std::make_shared<spdlog::logger>("frag_involved", begin(sinks), end(sinks));
    auto frag_not_involved = std::make_shared<spdlog::logger>("frag_not_involved", begin(sinks), end(sinks));

    // Register loggers to make them accessible globally
    spdlog::register_logger(global);
    spdlog::register_logger(chat);
    spdlog::register_logger(gameplay);
    spdlog::register_logger(edit);
    spdlog::register_logger(frag_involved);
    spdlog::register_logger(frag_not_involved);
}

}
}
