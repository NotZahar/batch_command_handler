#ifndef LOGGER_H
#define LOGGER_H

#include <string_view>

namespace handler {
    class Logger final {
    public:
        Logger(const Logger&) = delete;
        Logger(Logger&&) = delete;
        Logger& operator=(Logger const&) = delete;
        Logger& operator=(Logger &&) = delete;
        
        static Logger& instance();
        void log(const std::string& name, const std::string_view string) const;

    private:
        Logger() = default;
        ~Logger() = default;
    };
}

#endif // LOGGER_H