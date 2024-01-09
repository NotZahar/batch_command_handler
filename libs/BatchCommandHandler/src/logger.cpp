#include "logger.hpp"

namespace handler {
    Logger& Logger::instance() {
        static Logger instance;
        return instance;
    }

    void Logger::log(const std::string& name, std::string_view string) const {
        // impl
    }
}