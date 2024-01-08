#include "batch_command_handler.hpp"

#include <iostream>
#include <string>

#include "batch.hpp"
#include "parser.hpp"

namespace handler {
    BatchCommandHandler::BatchCommandHandler(int batchSize)
        : _batchSize(batchSize)
    {}

    void BatchCommandHandler::exec() {
        Batch<std::string> batch(_batchSize);
        for (std::string in; std::getline(std::cin, in);) {
            switch (Parser::identifyExpression(in)) {
            case Parser::expression::openingBrace:
                break;
            case Parser::expression::closingBrace:
                break;
            case Parser::expression::command:
                batch.append(in);
                break;
            }

            if (batch.size() == _batchSize) {
                std::cout << batch.serialize() << '\n';
                batch.clear();
            }
        }

        std::cout << batch.serialize() << '\n';
    }
}