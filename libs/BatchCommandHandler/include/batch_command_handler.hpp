#ifndef BATCH_COMMAND_HANDLER_H
#define BATCH_COMMAND_HANDLER_H

#include <filesystem>

namespace handler {
    class BatchCommandHandler {
    public:
        BatchCommandHandler() = delete;
        explicit BatchCommandHandler(int batchSize);

        ~BatchCommandHandler() = default;

        void exec();

    private:
        const int _batchSize;
    };
}

#endif // BATCH_COMMAND_HANDLER_H