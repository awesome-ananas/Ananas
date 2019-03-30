#ifndef __TOKENLIST_H
#define __TOKENLIST_H

#include "token.h"

#include <stdlib.h>

typedef struct __TokenNode
{
    struct __TokenNode *next;
    Token token;
} TokenNode;

typedef struct __TokenList
{
    TokenNode *head, *last;
    int length;
} TokenList;


TokenNode *TokenNode_new(TokenType _type, TokenValue _value);
void TokenNode_delete(TokenNode *node);

TokenList *TokenList_new(void);
void TokenList_delete(TokenList *list);
int TokenList_add(TokenList *list, Token token);
int TokenList_remove(TokenList *list, Token token);

#endif