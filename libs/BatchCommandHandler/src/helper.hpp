#ifndef HELPER_H
#define HELPER_H

#include <string>

namespace handler {
    struct messages {
        inline static const std::string BULK = "bulk";
        inline static const std::string BULK_CONTENT = "bulk:";
        inline static const std::string LOG_EXT = ".log";
    };
}

#endif // HELPER_H