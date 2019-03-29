#include "tokenlist.h"

#include "util.h"
#include <stdlib.h>
#include <string.h>

TokenList *
TokenList_new(void)
{
    TokenList *list;
    if ((list = calloc(1, sizeof(TokenList))) == NULL)
        goto cleanup;

    return list;

cleanup:
    return NULL;
}

void 
TokenList_delete(TokenList *self)
{
    TokenNode *iter = self->head;
    while(iter != NULL)
    {
        const TokenNode *freeTarget = iter;
        iter = iter->next;
        Token_delect(freeTarget);
    }
    free(self);
}

void 
TokenList_add(TokenList *self, TokenNode *node)
{
    if(self->head == NULL)
    {
        self->head = node;
    }
    else
    {
        self->last->next = node;
    }
    self->last = token;
}

int 
TokenList_remove(TokenList *self, TokenNode *node)
{
    TokenNode *iter = self->head;
    while(iter != NULL)
    {
        if(*iter == *node)
        {
            if(iter == self->last)
            {
                self->last = self->last->next;
            }
            else
            {
                
            }
            
            break;
        }
        iter = iter->next;
    }
}

Token *
Token_new(Tokenmeta _metadata, Tokentype _type, Literal _literal)
{
    Token *token;
    if ((token = calloc(1, sizeof(Token))) == NULL)
        goto cleanup;

    token->metadata = _metadata;
    token->type = _type;
    token->literal = _literal;
    return token;

cleanup:
    if (token != NULL)
        free(token);

    return NULL;
}

void Token_delect(Token *token)
{
    free(token);
}