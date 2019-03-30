#include "include/tokenlist.h"

#include <stdlib.h>
#include <string.h>

TokenNode *TokenNode_new(TokenType _type, TokenValue _value, Metadata _metadata)
{
    TokenNode *node;
    Token _token = { _type, _value };

    if( (node = calloc(1, sizeof(TokenNode))) == NULL)
        goto cleanup;
    
    node->next = NULL;
    node->token = _token;
    node->metadata = _metadata;
    
    return node;

cleanup:
    if(node != NULL)
        free(node);

    return NULL;
}

void TokenNode_delete(TokenNode *node)
{
    free(node);
}

TokenList *TokenList_new(void)
{
    TokenList *list;

    if( (list = calloc(1, sizeof(TokenList))) == NULL )
        goto cleanup;

    list->length = 0;
    list->head = NULL;
    list->last = NULL;

    return list;

cleanup:
    if(list != NULL)
        free(list);

    return NULL;
}

void TokenList_delete(TokenList *list)
{
    TokenNode *iter = list->head;

    while(iter != NULL)
    {
        TokenNode *target = iter;
        iter = iter->next;
        TokenNode_delete(target);
    }

    free(list);
}

int TokenList_add(TokenList *list, Token token, Metadata metadata)
{
    TokenNode *node;
    if((node = TokenNode_new(token.type, token.value, metadata)) == NULL)
        goto cleanup;

    if(list->head == NULL)
    {
        list->head = node;
    }
    else
    {
        list->last->next = node;        
    }
    list->last = node;

    list->length++;
    return 1;

cleanup:
    if(node != NULL)
        TokenNode_delete(node);

    return 0;
}

int TokenList_remove(TokenList *list, Token token)
{
    TokenNode *iter = list->head;
    TokenNode *prev = NULL;

    while(iter != NULL)
    {
        if(memcmp(&(iter->token), &token, sizeof(Token)) == 0)
        {
            if(prev == NULL)
            {
                list->head = iter->next;
            }
            else if(iter == list->last)
            {
                list->last = prev;
            }
            else
            {
                prev->next = iter->next;                
            }

            TokenNode_delete(iter);
            list->length--;

            return 1;
        }
        prev = iter;
        iter = iter->next;
    }
    
    return 0;
}