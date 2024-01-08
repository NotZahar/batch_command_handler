#ifndef PARSER_H
#define PARSER_H

#include <string_view>

namespace handler {
    class Parser {
    public:
        enum class expression {
            openingBrace,
            closingBrace,
            command
        };

        Parser() = default;

        ~Parser() = default;

        static expression identifyExpression(const std::string_view string);

        static constexpr std::string_view openingBraceTkn = "{";
        static constexpr std::string_view closingBraceTkn = "}";
    };
}

#endif // PARSER_H