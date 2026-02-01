/// @brief 
enum class TokenType {

    //Widly: I added numbers to the characters so we can know which character is which
    // for reference once we run the code


    // Single-character tokens
    LEFT_PAREN = 1, RIGHT_PAREN = 2, LEFT_BRACE = 3, RIGHT_BRACE = 4,
    COMMA = 5, DOT = 6, MINUS = 7, PLUS = 8, SEMICOLON = 9, SLASH = 10, STAR = 11,

    // Single or two-character tokens
    BANG = 12, BANG_EQUAL = 13,
    EQUAL = 14, EQUAL_EQUAL = 15,
    GREATER = 16, GREATER_EQUAL = 17,
    LESS = 18, LESS_EQUAL = 19,

    // Literals
    IDENTIFIER = 20, NUMBER = 21,

    // Keywords
    AND = 22, ELSE = 23, FALSE = 24, IF = 25, LET = 26, NIL = 27, OR = 28, TRUE = 29, WHILE = 30, PRINT = 31,

    // End of file
    END_OF_FILE = 32
};
