#ifndef TOKEN_H
#define TOKEN_H

#include "TokenType.h"
#include <string>

struct Token {
    TokenType type;
    std::string value;
    int line;

    Token(TokenType type, const std::string& value, int line)
        : type(type), value(value), line(line) {}
};

#endif
