#ifndef LEXER_H
#define LEXER_H

#define MAX_KEYWORDS 31
#define MAX_TOKEN_SIZE 100

typedef enum {
    KEYWORD,
    OPERATOR,
    SPECIAL_CHARACTER,
    CONSTANT,
    IDENTIFIER,
    UNKNOWN
} TokenType;

typedef struct {
    char lexeme[MAX_TOKEN_SIZE];
    TokenType type;
} Token;
const char* tokenTypeToString(TokenType type);
void initializeLexer(const char* filename);
Token getNextToken();
void categorizeToken(Token* token);
int isKeyword(const char* str);
int isOperator(const char* str);
int isSpecialCharacter(char ch);
int isConstant(const char* str);
int isIdentifier(const char* str);

#endif
