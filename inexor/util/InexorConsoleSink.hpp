/// @file Sink for the inexor game console.

#pragma once

#include <string>
#include <iostream>
#include "spdlog/sinks/sink.h"

/// Function which displayes console text ingame.
extern void conline(int type, const char *sf);

namespace inexor {
namespace util {

    class InexorConsoleSink : public spdlog::sinks::sink
    {
    public:
        void log(const spdlog::details::log_msg& msg) override
        {
            int type = 0;
            // Convert loggers and levels to legacy conline types:
            switch (msg.level)
            {
                default:
                case spdlog::level::info:
                    type = 1<<0;
                    break;
                case spdlog::level::warn:
                    type = 1<<1;
                    break;
                case spdlog::level::err:
                    type = 1<<2;
                    break;
                case spdlog::level::debug:
                    type = 1<<3;
                    break;
            }
            std::string str = msg.formatted.str();
            str.erase(std::remove(str.begin(), str.end(), '\n'), str.end());
            conline(type, str.c_str());
        }
        void flush() override {};
    };

}
}
