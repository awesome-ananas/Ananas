#include "include/lexer.h"

#include "include/token.h"
#include "include/tokenlist.h"
#include <stdlib.h>
#include <stdio.h>
#include <ctype.h>
#include <string.h>

static const Token Token_LPARN = {TokenType_LPARN, {0}};
static const Token Token_RPARN = {TokenType_RPARN, {0}};
static const Token Token_CONS = {TokenType_CONS, {0}};
static const Token Token_LIST = {TokenType_LIST, {0}};
static const Token Token_EOF = {TokenType_EOF, {0}};

static inline char Lexer_peek(Lexer *self);
static inline char Lexer_pop(Lexer *self);
static void Lexer_lexNumber(Lexer *self);
static void Lexer_lexString(Lexer *self);
static void Lexer_lexSymbol(Lexer *self);
static void Lexer_commentConsume(Lexer *self);
static void Lexer_spaceConsume(Lexer *self);
static void Lexer_newlineConsume(Lexer *self);
static int Lexer_isWhitespace(Lexer *self);
static int Lexer_isNewline(Lexer *self);

Lexer *Lexer_new(char *_code)
{
    Lexer *lexer;
    if ((lexer = calloc(1, sizeof(Lexer))) == NULL)
        goto cleanup;
    if ((lexer->tokens = TokenList_new()) == NULL)
        goto cleanup;

    lexer->code = _code;
    return lexer;

cleanup:
    if (lexer->tokens != NULL)
        TokenList_delete(lexer->tokens);
    if (lexer != NULL)
        free(lexer);

    return NULL;
}

void Lexer_delete(Lexer *self)
{
    TokenList_delete(self->tokens);
    free(self);
}

void Lexer_lex(Lexer *self)
{
    char peek;
    while ((peek = Lexer_peek(self)) != '\0')
    {
        if (peek == ';')
        {
            Lexer_commentConsume(self);
        }
        else if (peek == '(')
        {
            TokenList_add(self->tokens, Token_LPARN);
            Lexer_pop(self);
        }
        else if (peek == ')')
        {
            TokenList_add(self->tokens, Token_RPARN);
            Lexer_pop(self);
        }
        else if (peek == ':')
        {
            TokenList_add(self->tokens, Token_CONS);
            Lexer_pop(self);
        }
        else if (peek == '\'')
        {
            TokenList_add(self->tokens, Token_LIST);
            Lexer_pop(self);
        }
        else if (peek == EOF)
        {
            TokenList_add(self->tokens, Token_EOF);
            Lexer_pop(self);
        }
        else if (Lexer_isWhitespace(self))
        {
            Lexer_spaceConsume(self);
        }
        else if (Lexer_isNewline(self))
        {
            Lexer_newlineConsume(self);
        }
        else if (isdigit(peek))
        {
            Lexer_lexNumber(self);
        }
        else if (peek == '\"')
        {
            Lexer_lexString(self);
        }
        else if (isalpha(peek) || peek == '_')
        {
            Lexer_lexSymbol(self);
        }
        else
        {
            fprintf(stderr, "%c is unreconiged\n", peek);
            break;
        }
    }
}

static inline char Lexer_peek(Lexer *self)
{
    return self->code[self->index];
}

static inline char Lexer_pop(Lexer *self)
{
    // putchar(self->code[self->index]);
    return self->code[self->index++];
}

static void Lexer_commentConsume(Lexer *self)
{
    while (Lexer_peek(self) == ';')
        Lexer_pop(self);

    while (!Lexer_isNewline(self))
        Lexer_pop(self);

    Lexer_newlineConsume(self);
}
static void Lexer_lexNumber(Lexer *self)
{
    Token token;
    char *begin = self->code + self->index;
    int isfloating = 0;

    while (1)
    {
        char peek = Lexer_peek(self);
        if (isdigit(peek) || peek == '.')
        {
            if (peek == '.')
            {
                if(isfloating == 1)
                {
                    // make an error
                }
                else
                    isfloating = 1;
            }
            Lexer_pop(self);
        }
        else
            break;
    }

    if (isfloating)
    {
        token.type = TokenType_FLOATING;
        token.value.floating = strtod(begin, NULL);
    }
    else
    {
        token.type = TokenType_INTEGER;
        token.value.integer = strtol(begin, NULL, 10);
    }

    TokenList_add(self->tokens, token);
}
static void Lexer_lexString(Lexer *self)
{
}
static void Lexer_lexSymbol(Lexer *self)
{
}
static void Lexer_spaceConsume(Lexer *self)
{
    while (Lexer_isWhitespace(self))
        Lexer_pop(self);
}
static void Lexer_newlineConsume(Lexer *self)
{
    while (Lexer_isNewline(self))
        Lexer_pop(self);
}
static int Lexer_isWhitespace(Lexer *self)
{
    const char peek = Lexer_peek(self);
    return (peek == ' ') || (peek == '\t') || (peek == '\v');
}
static int Lexer_isNewline(Lexer *self)
{
    const char peek = Lexer_peek(self);
    return (peek == '\n') || (peek == '\r');
}