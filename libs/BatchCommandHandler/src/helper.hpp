#ifndef HELPER_H
#define HELPER_H

#include <string>

namespace handler {
    struct messages {
        inline static const std::string BULK = "bulk:";
        inline static const std::string EMPTY_BATCH = "no items";
    };
}

#endif // HELPER_H