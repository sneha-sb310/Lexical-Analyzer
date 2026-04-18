#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include "lexer.h"

static const char *keywords[MAX_KEYWORDS] = {
    "char", "double", "enum", "float", "int", "long",
    "short", "signed", "union", "unsigned", "void",
    "break", "case", "continue", "default", "do",
    "else", "for", "goto", "if", "switch", "while",
    "auto", "extern", "register", "static",
    "const", "sizeof", "typedef", "volatile",
    "return"};

static const char *operators = "+-*/%=!<>|&";
static const char *specialCharacters = ",;{}()[]";
static FILE *srcFile;
void initializeLexer(const char *filename)
{
    srcFile = fopen(filename, "r");
    if (srcFile == NULL)
        printf("File open failed");
}
const char *tokenTypeToString(TokenType type)
{
    switch (type)
    {
    case KEYWORD:
        return "KEYWORD";
    case OPERATOR:
        return "OPERATOR";
    case SPECIAL_CHARACTER:
        return "SPECIAL_CHARACTER";
    case CONSTANT:
        return "CONSTANT";
    case IDENTIFIER:
        return "IDENTIFIER";
    default:
        return "UNKNOWN";
    }
}

Token getNextToken()
{
    Token token;
    token.type = UNKNOWN;

    char ch = fgetc(srcFile);
    if (ch == EOF)
        return token;

    while (isspace(ch))
    {
        ch = fgetc(srcFile);
        if (ch == EOF)
            return token;
    }

    if (isalpha(ch) || ch == '_')
    {
        token.lexeme[0] = ch;
        int i = 1;
        char next_char = fgetc(srcFile);

        while (isalnum(next_char) || next_char == '_')
        {
            token.lexeme[i] = next_char;
            i++;
            next_char = fgetc(srcFile);
        }

        ungetc(next_char, srcFile);
        token.lexeme[i] = '\0';

        categorizeToken(&token);
        return token;
    }
    else if (isdigit(ch))
    {
        token.lexeme[0] = ch;
        int i = 1;
        char next_char = fgetc(srcFile);

        while (isdigit(next_char))
        {
            token.lexeme[i] = next_char;
            i++;
            next_char = fgetc(srcFile);
        }

        ungetc(next_char, srcFile);
        token.lexeme[i] = '\0';
        token.type = CONSTANT;
        return token;
    }
    else if (isOperator((char[]){ch, '\0'}))
    {
        token.lexeme[0] = ch;
        token.lexeme[1] = '\0';
        token.type = OPERATOR;
        return token;
    }
    else if (isSpecialCharacter(ch))
    {
        token.lexeme[0] = ch;
        token.lexeme[1] = '\0';
        token.type = SPECIAL_CHARACTER;
        return token;
    }
    else
    {
        token.lexeme[0] = ch;
        token.lexeme[1] = '\0';
        token.type = UNKNOWN;
        return token;
    }
}
void categorizeToken(Token *token)
{
    if (isKeyword(token->lexeme))
        token->type = KEYWORD;
    else if (isOperator(token->lexeme))
        token->type = OPERATOR;
    else if (isConstant(token->lexeme))
        token->type = CONSTANT;
    else if (isIdentifier(token->lexeme))
        token->type = IDENTIFIER;
    else
        token->type = UNKNOWN;
}
int isKeyword(const char *str)
{
    for (int i = 0; i < MAX_KEYWORDS; i++)
    {
        if (!(strcmp(str, keywords[i])))
            return 1;
    }
    return 0;
}
int isOperator(const char *str)
{
    int i = 0;
    if (strlen(str) == 1)
    {
        char *op = strchr(operators, str[0]);
        if (op != NULL)
            return 1;
    }
    return 0;
}
int isSpecialCharacter(char ch)
{
    char *chr = strchr(specialCharacters, ch);
    if (chr != NULL)
        return 1;
    return 0;
}
int isConstant(const char *str)
{
    if (str == NULL)
        return 0;
    int i = 0;
    while (str[i] != '\0')
    {
        char ch = str[i];
        if (!(isdigit(ch)))
            return 0;
        i++;
    }
    return 1;
}
int isIdentifier(const char *str)
{
    if (str == NULL)
        return 0;

    if (!(isalpha(str[0])) && str[0] != '_')
        return 0;

    int i = 1;
    while (str[i] != '\0')
    {
        char ch = str[i];
        if (!(isalnum(ch)) && ch != '_')
            return 0;
        i++;
    }
    if (isKeyword(str))
        return 0;
    return 1;
}