#ifndef __LEXER_H
#define __LEXER_H

#include "token.h"
#include "vector.h"

typedef struct
{
    char *code;
    size_t index;
    Vector *tokens;
} Lexer;

#endif