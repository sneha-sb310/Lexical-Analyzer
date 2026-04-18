#include <stdio.h>
#include "lexer.h"

int main(int argc, char *argv[]) {
    initializeLexer(argv[1]);

    Token token;
    while ((token = getNextToken()).type != UNKNOWN) {
        printf("Token :\t%s\t\tType :\t%s\n", token.lexeme, tokenTypeToString(token.type));
    }

    return 0;
}
