#ifndef __LEXER_H
#define __LEXER_H

#include "token.h"
#include "tokenlist.h"
#include <unistd.h>

typedef struct
{
    char *code;
    int index;
    int row, colum;
    TokenList tokens;
} Lexer;

Lexer *Lexer_new(char *_code);
void Lexer_lex(Lexer *self);
void Lexer_delete(Lexer *self);

#endif