#include "logger.hpp"

#include <iostream>
#include <fstream>
#include <chrono>

#include "helper.hpp"

namespace handler {
    Logger& Logger::instance() {
        static Logger instance;
        return instance;
    }

    void Logger::log(const std::string& string) const {
        std::cout << string << '\n';
        
        const auto now = std::chrono::system_clock::now();
        const auto logName = messages::BULK + std::to_string(std::chrono::duration_cast<std::chrono::seconds>(now.time_since_epoch()).count());
        std::ofstream logFile(logName + messages::LOG_EXT);
        logFile << string << '\n';
        logFile.close();
    }
}