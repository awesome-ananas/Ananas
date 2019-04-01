#include "include/lexer.h"

#include "include/token.h"
#include "include/tokenlist.h"
#include <stdlib.h>
#include <stdio.h>
#include <ctype.h>
#include <string.h>

static const Token Token_LPARN = { (enum __TokenType) TokenType_LPARN, { 0 } };
static const Token Token_RPARN = { (enum __TokenType) TokenType_RPARN, { 0 } };
static const Token Token_CONS = { (enum __TokenType) TokenType_CONS, { 0 } };
static const Token Token_LIST = { (enum __TokenType) TokenType_LIST, { 0 } };
static const Token Token_EOF = { (enum __TokenType) TokenType_EOF, { 0 } };

static const char *const SYMBOL_SET = "+-/*\%=?!_";

static inline char Lexer_peek(Lexer *self);
static inline char Lexer_pop(Lexer *self);
static void Lexer_lexNumber(Lexer *self);
static void Lexer_lexBoolean(Lexer *self);
static void Lexer_lexString(Lexer *self);
static void Lexer_lexSymbol(Lexer *self);
static void Lexer_commentConsume(Lexer *self);
static void Lexer_spaceConsume(Lexer *self);
static void Lexer_newlineConsume(Lexer *self);
static Metadata Lexer_getMetadata(Lexer *self);

static inline int Lexer_isWhitespace(const char peek);
static inline int Lexer_isNewline(const char peek);
static inline int Lexer_isSymbolCharacter(const char peek);
static inline int Lexer_isFirstSymbolCharacter(const char peek);

Lexer *Lexer_new(char *_code)
{
    Lexer *lexer;
    if ((lexer = calloc(1, sizeof(Lexer))) == NULL)
        goto cleanup;
    if ((lexer->tokens = TokenList_new()) == NULL)
        goto cleanup;

    lexer->row = 1;
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
            Lexer_commentConsume(self);

        else if (peek == '(')
        {
            TokenList_add(self->tokens, Token_LPARN, Lexer_getMetadata(self));
            Lexer_pop(self);
        }
        else if (peek == ')')
        {
            TokenList_add(self->tokens, Token_RPARN, Lexer_getMetadata(self));
            Lexer_pop(self);
        }
        else if (peek == ':')
        {
            TokenList_add(self->tokens, Token_CONS, Lexer_getMetadata(self));
            Lexer_pop(self);
        }
        else if (peek == '\'')
        {
            TokenList_add(self->tokens, Token_LIST, Lexer_getMetadata(self));
            Lexer_pop(self);
        }
        else if (peek == EOF)
        {
            TokenList_add(self->tokens, Token_EOF, Lexer_getMetadata(self));
            Lexer_pop(self);
        }
        
        else if (Lexer_isWhitespace(peek))
            Lexer_spaceConsume(self);

        else if (Lexer_isNewline(peek))
            Lexer_newlineConsume(self);

        else if (isdigit(peek))
            Lexer_lexNumber(self);

        else if (peek == '#')
            Lexer_lexBoolean(self);

        else if (peek == '\"')
            Lexer_lexString(self);

        else if (Lexer_isFirstSymbolCharacter(peek))
            Lexer_lexSymbol(self);

        else
        {
            fprintf(stderr, "\n\tunreconiged input: %c\n", peek);
            break;
        }
    }
}

static inline char Lexer_peek(Lexer *self)
{
    return self->code[self->index];
}

static char Lexer_pop(Lexer *self)
{
    if (Lexer_isNewline(Lexer_peek(self)))
    {
        self->row++;
        self->colum = 1;
    }
    else
        self->colum++;

    return self->code[self->index++];
}

static void Lexer_commentConsume(Lexer *self)
{
    while (Lexer_peek(self) == ';')
        Lexer_pop(self);

    while (!Lexer_isNewline(Lexer_peek(self)))
        Lexer_pop(self);

    Lexer_newlineConsume(self);
}
static void Lexer_lexNumber(Lexer *self)
{
    Token token;
    Metadata metadata = Lexer_getMetadata(self);
    char *begin = self->code + self->index;
    int isfloating = 0;

    while (1)
    {
        char peek = Lexer_peek(self);
        if (isdigit(peek) || peek == '.')
        {
            if (peek == '.')
            {
                if (isfloating == 1)
                {
                    fprintf(stderr, "Expected digits, but dot\n");
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

    TokenList_add(self->tokens, token, metadata);
}
 static void Lexer_lexBoolean(Lexer *self)
{
    char c;
    Token token = { 0, };
    Metadata metadata = Lexer_getMetadata(self);
    token.type = TokenType_BOOLEAN;

    Lexer_pop(self);
    c = Lexer_pop(self);

    if(c == 't')
        token.value.boolean = 1;

    else if(c == 'f')
        token.value.boolean = 0;

    else
        fprintf(stderr, "Expected #t or #f, but #%c\n", c);
    
    TokenList_add(self->tokens, token, metadata);
}

static void Lexer_lexString(Lexer *self)
{
    int i = 0;
    char c;
    Token _token = { 0, };
    Metadata metadata = Lexer_getMetadata(self);
    _token.type = TokenType_STRING;

    Lexer_pop(self);
    while ((c = Lexer_peek(self)) != '\"')
    {
        _token.value.string[i++] = c;
        Lexer_pop(self);
    }
    Lexer_pop(self);

    TokenList_add(self->tokens, _token, metadata);
}

static void Lexer_lexSymbol(Lexer *self)
{
    int i = 0;
    Token _token = {0, };
    Metadata metadata = Lexer_getMetadata(self);
    _token.type = TokenType_SYMBOL;

    while (Lexer_isSymbolCharacter(Lexer_peek(self)))
        _token.value.symbol[i++] = Lexer_pop(self);

    TokenList_add(self->tokens, _token, metadata);
}

static void Lexer_spaceConsume(Lexer *self)
{
    while (Lexer_isWhitespace(Lexer_peek(self)))
        Lexer_pop(self);
}

static void Lexer_newlineConsume(Lexer *self)
{
    while (Lexer_isNewline(Lexer_peek(self)))
        Lexer_pop(self);
}

static inline int Lexer_isWhitespace(const char peek)
{
    return (peek == ' ') || (peek == '\t') || (peek == '\v');
}

static inline int Lexer_isNewline(const char peek)
{
    return (peek == '\n') || (peek == '\r');
}

static inline int Lexer_isSymbolCharacter(const char peek)
{
    return (isalnum(peek) || strchr(SYMBOL_SET, peek));
}

static inline int Lexer_isFirstSymbolCharacter(const char peek)
{
    return (isalpha(peek) || strchr(SYMBOL_SET, peek));
}

static Metadata Lexer_getMetadata(Lexer *self)
{
    Metadata metadata = { self->row, self->colum };
    return metadata;
}
