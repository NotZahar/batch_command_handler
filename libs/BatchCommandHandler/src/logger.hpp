#ifndef LOGGER_H
#define LOGGER_H

namespace handler {
    class Logger final {
    public:
        Logger(const Logger&) = delete;
        Logger(Logger&&) = delete;
        Logger& operator=(Logger const&) = delete;
        Logger& operator=(Logger &&) = delete;
        
        static Logger& instance();

    private:
        Logger() = default;
        ~Logger() = default;
    };
}

#endif // LOGGER_H