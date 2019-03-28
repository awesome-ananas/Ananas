#include "lexer.h"

#include "token.h"
#include "util.h"
#include "vector.h"
#include <stdlib.h>
#include <stdbool.h>

static extern inline char Lexer_peek(Lexer *self);
static extern inline char Lexer_pop(Lexer *self);
static extern inline bool Lexer_isEOF(Lexer *self);

Lexer *Lexer_new(char *_code)
{
    Lexer *lexer;
    if((lexer = calloc(1, sizeof(Lexer))) == NULL)
        goto cleanup;
    if((lexer->tokens = Vector_new()) == NULL)
        goto cleanup;

    lexer->code = _code;
    lexer->index = 0;
    return lexer;

cleanup:
    if(lexer->tokens != NULL)
        Vector_delete(&lexer->tokens);
    if(lexer != NULL)
        free(lexer);

    return NULL;
}

void Lexer_lex(Lexer *self)
{
    for(;;)
    {
        const char peek = Lexer_peek();
        switch (peek)
        {
            case ';':
                break;

            case '(':
                break;

            case ')':
                break;

            case '.':
                break;

            case ' ':
            case '\t':
                break;

            case '\r':
            case '\n':
                break;

            case '0' ... '9':
                Lexer_number(self);
                break;
            
            case 'a' ... 'z':
            case 'A' ... 'Z':
            case '_':
                Lexer_symbol(self);

            default:
                break;
        }
    }
}

void Lexer_delete(Lexer *self)
{
    free(self);
}

static extern inline char Lexer_peek(Lexer *self)
{
    return self->code[(self->index)];
}

static extern inline char Lexer_pop(Lexer *self)
{
    return self->code[(self->tokens++)];
}

static extern inline bool Lexer_isEOF(Lexer *self)
{
    
}