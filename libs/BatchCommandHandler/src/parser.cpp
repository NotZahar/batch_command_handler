#include "parser.hpp"

#include <iostream>
#include <string>

namespace handler {
    Parser::expression Parser::identifyExpression(const std::string_view string) {
        if (string == openingBraceTkn) {
            return expression::openingBrace;
        } else if (string == closingBraceTkn) {
            return expression::closingBrace;
        } else {
            return expression::command;
        }
    }
}