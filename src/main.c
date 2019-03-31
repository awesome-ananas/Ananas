#include <stdio.h>
#include "include/lexer.h"

int main(int argc, const char *argv[])
{
    int i=0;
    char c, input[0xFFFF] = {0, };
    while((c = getchar()) != EOF)
        input[i++] = c;

    Lexer *lexer = Lexer_new(input);
    TokenNode *iter;

    Lexer_lex(lexer);
    for (iter = lexer->tokens->head; iter != NULL; iter = iter->next)
        TokenNode_show(*iter);
    Lexer_delete(lexer);
    return 0;
}
