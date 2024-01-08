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
        SBatch<std::string> sbatch(_batchSize);
        DBatch<std::string> dbatch(_batchSize);
        for (std::string in; std::getline(std::cin, in);) {
            switch (Parser::identifyExpression(in)) {
            case Parser::expression::openingBrace:
                sbatch.end();
                dbatch.addBlock();
                break;
            case Parser::expression::closingBrace:
                dbatch.end();
                break;
            case Parser::expression::command:
                if (dbatch.blockExists()) {
                    dbatch.append(in);
                    continue;
                }
                
                sbatch.append(in);
                break;
            }

            if (sbatch.size() == _batchSize)
                sbatch.end();
        }

        sbatch.end();
    }
}