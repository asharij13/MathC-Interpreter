#include <iostream>
#include <string>
#include <vector>
#include <cctype>
#include <unordered_map>
#include <memory>
#include <stdexcept>

/*1. Tokenization (Lexer)
The lexer reads the source code character by character and groups them into meaningful tokens. */

#ifndef Tokenization
#define Tokenization

// DEFINE HERE YOUR TokenType CLASS 
enum class TokenType {
    // Define token types here
    LEFT_PAREN, RIGHT_PAREN, LEFT_BRACE, RIGHT_BRACE,
    COMMA, DOT, MINUS, PLUS, SEMICOLON, STAR,
    SLASH, NUMBER, STRING, IDENTIFIER,
    AND, CLASS, ELSE, FALSE, FOR, FUN, IF, NIL, 
    OR, PRINT, RETURN, SUPER, THIS, TRUE, VAR, WHILE, END_OF_FILE
};

// DEFINE HERE YOUR Token struct 
struct Token {
    TokenType type;
    std::string lexeme;
    std::string literal;
    int line;

    Token(TokenType type, std::string lexeme, std::string literal, int line)
        : type(type), lexeme(lexeme), literal(literal), line(line) {}
};

class Lexer {
public:
    Lexer(const std::string& source) { 
        this->source = source;
        start = 0;
        current = 0;
        line = 1;
        keywords = {
            {"and", TokenType::AND}, {"class", TokenType::CLASS},
            {"else", TokenType::ELSE}, {"false", TokenType::FALSE},
            {"for", TokenType::FOR}, {"fun", TokenType::FUN},
            {"if", TokenType::IF}, {"nil", TokenType::NIL},
            {"or", TokenType::OR}, {"print", TokenType::PRINT},
            {"return", TokenType::RETURN}, {"super", TokenType::SUPER},
            {"this", TokenType::THIS}, {"true", TokenType::TRUE},
            {"var", TokenType::VAR}, {"while", TokenType::WHILE}
        };
    }

    std::vector<Token> scanTokens() {
        while (!isAtEnd()) { 
            start = current;
            scanToken();
        }

        tokens.emplace_back(TokenType::END_OF_FILE, "", "", line);
        return tokens;
    }

private:
    std::string source;
    std::vector<Token> tokens;
    std::unordered_map<std::string, TokenType> keywords;

    size_t start;
    size_t current;
    int line;

    bool isAtEnd() const { 
        return current >= source.size(); 
    }

    char advance() {
        return source[current++];
    }

    void addToken(TokenType type) { 
        addToken(type, ""); 
    }

    void addToken(TokenType type, const std::string& literal) { 
        std::string text = source.substr(start, current - start);
        tokens.emplace_back(type, text, literal, line);
    }

    bool match(char expected) {
        if (isAtEnd()) return false;
        if (source[current] != expected) return false;
        current++;
        return true;
    }

    char peek() const { 
        return isAtEnd() ? '\0' : source[current]; 
    }

    void scanToken() {
        char c = advance();
        switch (c) {
            case '(': addToken(TokenType::LEFT_PAREN); break;
            case ')': addToken(TokenType::RIGHT_PAREN); break;
            case '{': addToken(TokenType::LEFT_BRACE); break;
            case '}': addToken(TokenType::RIGHT_BRACE); break;
            case ',': addToken(TokenType::COMMA); break;
            case '.': addToken(TokenType::DOT); break;
            case '-': addToken(TokenType::MINUS); break;
            case '+': addToken(TokenType::PLUS); break;
            case ';': addToken(TokenType::SEMICOLON); break;
            case '*': addToken(TokenType::STAR); break;
            case '/':
                if (match('/')) {
                    // A comment goes until the end of the line.
                    while (peek() != '\n' && !isAtEnd()) advance();
                } else {
                    addToken(TokenType::SLASH);
                }
                break;
            case '"': string(); break;
            default:
                if (std::isdigit(c)) {
                    number();
                } else if (std::isalpha(c) || c == '_') {
                    identifier();
                } else {
                    std::cerr << "Unexpected character at line " << line << ": " << c << "\n";
                }
                break;
        }
    }

    void string() {
        while (peek() != '"' && !isAtEnd()) {
            if (peek() == '\n') line++;
            advance();
        }

        if (isAtEnd()) {
            std::cerr << "Unterminated string at line " << line << ".\n";
            return;
        }

        advance();

        std::string value = source.substr(start + 1, current - start - 2);
        tokens.emplace_back(TokenType::STRING, value, value, line);
    }

    void number() {
        while (std::isdigit(peek())) advance();

        if (peek() == '.' && std::isdigit(peekNext())) {
            advance();
            while (std::isdigit(peek())) advance();
        }

        addToken(TokenType::NUMBER);
    }

    char peekNext() const { 
        if (current + 1 >= source.length()) return '\0';
        return source[current + 1];
    }

    void identifier() {
        while (std::isalnum(peek()) || peek() == '_') advance();

        std::string text = source.substr(start, current - start);
        TokenType type = TokenType::IDENTIFIER;
        if (keywords.find(text) != keywords.end()) {
            type = keywords[text];
        }
        addToken(type);
    }
};

#endif
