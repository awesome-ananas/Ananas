#ifndef __LEXER_C
#define __LEXER_C

#include "tokenlist.h"

typedef struct __Lexer
{
    TokenList *tokens;
    char *code;
    int index;
    int row, colum;
} Lexer;

Lexer *Lexer_new(char *_code);
void Lexer_delete(Lexer *self);
void Lexer_lex(Lexer *self);

#endif