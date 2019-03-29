#include "lexer.h"

#include "token.h"
#include "tokenlist.h"
#include "util.h"
#include "vector.h"
#include <stdlib.h>
#include <stdbool.h>
#include <ctype.h>
#include <stdio.h>

static inline char Lexer_peek(Lexer *self);
static inline char Lexer_pop(Lexer *self);
static inline bool isEOF(const char c);
static inline bool iswhitespace(const char c);

Lexer *Lexer_new(char *_code)
{
    Lexer *lexer;
    if ((lexer = calloc(1, sizeof(Lexer))) == NULL)
        goto cleanup;
    if ((lexer->tokens = TokenList_new()) == NULL)
        goto cleanup;

    lexer->code = _code;
    lexer->index = 0;
    return lexer;

cleanup:
    if (lexer->tokens != NULL)
        Vector_delete(&lexer->tokens);
    if (lexer != NULL)
        free(lexer);

    return NULL;
}

void Lexer_lex(Lexer *self)
{
    for (;;)
    {
        const char peek = Lexer_peek(self);
        if (peek == ';')
        {
        }
        else if (peek == '(')
        {
            Tokenmeta meta = {lexer->row, lexer->colum};
            Token token = { meta, Tokentype_LPARN, 0 };
            Lexer_pop(self);
        }
        else if (peek == ')')
        {
        }
        else if (peek == '.')
        {

        }
        else if (isdigit(peek))
        {
        }
        else if (isalpha(peek))
        {
        }
        else if (iswhitespace(peek))
        {
        }
        else if (isEOF(peek))
        {
        }
        else
        {
        }
    }
}

void Lexer_delete(Lexer *self)
{
    free(self);
}

static inline char Lexer_peek(Lexer *self)
{
    return self->code[(self->index)];
}

static inline char Lexer_pop(Lexer *self)
{
    return self->code[(self->index++)];
}

static inline bool isEOF(const char c)
{
    return (c == EOF);
}

static inline bool iswhitespace(const char c)
{
    return ((c == ' ') || (c == '\t') || (c == '\v'));
}

static inline bool isnewline(const char c)
{
    return ((c == '\n') || (c == '\r'));
}

static void Lexer_lexList(Lexer *self)
{
}