#include <stdio.h>
#include "include/lexer.h"

void Show_token(Token t)
{
    switch (t.type)
    {
    case TokenType_LPARN:
        printf("Token = { Left paren }\n");
        break;

    case TokenType_RPARN:
        printf("Token = { Right paren }\n");
        break;

    case TokenType_CONS:
        printf("Token = { Cons }\n");
        break;

    case TokenType_LIST:
        printf("Token = { List }\n");
        break;

    case TokenType_EOF:
        printf("Token = { EOF }\n");
        break;

    case TokenType_INTEGER:
        printf("TokenWithValue = { %d }\n", t.value.integer);
        break;

    case TokenType_FLOATING:
        printf("TokenWithValue = { %lf }\n", t.value.floating);
        break;

    case TokenType_STRING:
        printf("TokenWithValue = { \"%s\" }\n", t.value.string);
        break;

    case TokenType_SYMBOL:
        printf("TokenWithValue = { %s }\n", t.value.symbol);
        break;

    default:
        break;
    }
}

int main(int argc, const char *argv[])
{
    Lexer *lexer = Lexer_new("; The first Ananas program.\n(display \"This is ananas\")\n");
    TokenNode *iter;

    Lexer_lex(lexer);
    for (iter = lexer->tokens->head; iter != NULL; iter = iter->next)
        Show_token(iter->token);

    Lexer_delete(lexer);
    return 0;
}
