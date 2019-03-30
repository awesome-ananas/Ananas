#include <stdio.h>
#include "include/lexer.h"
void Show_token(TokenNode *n)
{
    switch (n->token.type)
    {
    case TokenType_LPARN:
        printf("%d:%d, Token = { Left paren }\n", n->metadata.row, n->metadata.colum);
        break;

    case TokenType_RPARN:
        printf("%d:%d, Token = { Right paren }\n", n->metadata.row, n->metadata.colum);
        break;

    case TokenType_CONS:
        printf("%d:%d, Token = { Cons }\n", n->metadata.row, n->metadata.colum);
        break;

    case TokenType_LIST:
        printf("%d:%d, Token = { List }\n", n->metadata.row, n->metadata.colum);
        break;

    case TokenType_EOF:
        printf("%d:%d, Token = { EOF }\n", n->metadata.row, n->metadata.colum);
        break;

    case TokenType_INTEGER:
        printf("%d:%d, TokenWithValue = { %d }\n", n->metadata.row, n->metadata.colum, n->token.value.integer);
        break;

    case TokenType_FLOATING:
        printf("%d:%d, TokenWithValue = { %lf }\n", n->metadata.row, n->metadata.colum, n->token.value.floating);
        break;

    case TokenType_STRING:
        printf("%d:%d, TokenWithValue = { \"%s\" }\n", n->metadata.row, n->metadata.colum, n->token.value.string);
        break;

    case TokenType_SYMBOL:
        printf("%d:%d, TokenWithValue = { %s }\n", n->metadata.row, n->metadata.colum, n->token.value.symbol);
        break;

    default:
        break;
    }
}

int main(int argc, const char *argv[])
{
    Lexer *lexer = Lexer_new("; The second Ananas program.\n(display \"This is ananas\")\n\t(define (neg x) (- 0 x))");
    TokenNode *iter;

    Lexer_lex(lexer);
    for (iter = lexer->tokens->head; iter != NULL; iter = iter->next)
        Show_token(iter);

    Lexer_delete(lexer);
    return 0;
}
