#include "logger.hpp"

namespace handler {
    Logger& Logger::instance() {
        static Logger instance;
        return instance;
    }
}