#include <iostream>
#include <string>
#include <vector>
#include "tokenization.cpp"  // Include the header, not the .cpp

// Function to convert TokenType to string for easier display
std::string tokenTypeToString(TokenType type) {
    switch (type) {
        case TokenType::IDENTIFIER: return "IDENTIFIER";
        case TokenType::NUMBER: return "NUMBER";
        case TokenType::PRINT: return "PRINT";
        case TokenType::PLUS: return "PLUS";
        // Add more cases as needed
        default: return "UNKNOWN";
    }
}

int main() {
    std::string source = R"(
    let x = 534;
    let y = 10;
    print x + y;
    )";

    Lexer lexer(source);
    std::vector<Token> tokens = lexer.scanTokens();

    for (Token& item: tokens) {
        std::cout << item.lexeme << " line " << item.line << " Tokenization " << tokenTypeToString(item.type) << std::endl;
    }

    return 0;
}
