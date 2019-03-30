#include <stdio.h>
#include "include/lexer.h"

int main(int argc, const char *argv[])
{
    Lexer *lexer = Lexer_new("177.50\n\t;;;This is Ananas!\n\t; Test case ;\n\t\t0.000123\n");
    TokenNode *iter;

    Lexer_lex(lexer);

    for (iter = lexer->tokens->head; iter != NULL; iter = iter->next)
        printf("%d %lf\n", iter->token.type, iter->token.value.floating);

    Lexer_delete(lexer);
    return 0;
}
