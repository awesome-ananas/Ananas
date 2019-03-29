#ifndef __LIST_H
#define __LIST_H

#include "token.h"

typedef struct
{
    TokenNode *head, *last;
    size_t length;
} TokenList;

typedef struct
{
    Token value;
    TokenList *next, *prev;
} TokenNode;

TokenList *TokenList_new(void); /* Create token list. Return NULL when it failed. */
void TokenList_delete(TokenList *self);
int TokenList_add(TokenList *self, Token token);
int TokenList_remove(TokenList *, Token Token);

#endif