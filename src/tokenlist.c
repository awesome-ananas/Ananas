#include "include/tokenlist.h"

#include <stdlib.h>
#include <string.h>
#include <stdio.h>

TokenNode *TokenNode_new(TokenType _type, TokenValue _value, Metadata _metadata)
{
    TokenNode *node;
    Token _token = {_type, _value};

    if ((node = calloc(1, sizeof(TokenNode))) == NULL)
        goto cleanup;

    node->next = NULL;
    node->token = _token;
    node->metadata = _metadata;

    return node;

cleanup:
    if (node != NULL)
        free(node);

    return NULL;
}
void TokenNode_delete(TokenNode *node)
{
    free(node);
}
void TokenNode_show(TokenNode node)
{
    TokenType _type = node.token.type;
    int _row = node.metadata.row, _colum = node.metadata.colum; 

    switch (_type)
    {
    case TokenType_INTEGER:
        printf("{ %d:%d %d }\n", _row, _colum, node.token.value.integer);
        break;

    case TokenType_BOOLEAN:
        printf(node.token.value.boolean ?
            "{ %d:%d #t }\n" :
            "{ %d:%d #f }\n", _row, _colum);
        break;

    case TokenType_STRING:
        printf("{ %d:%d \"%s\" }\n", _row, _colum, node.token.value.string);
        break;

    case TokenType_SYMBOL:
        printf("{ %d:%d %s }\n", _row, _colum, node.token.value.symbol);
        break;

    case TokenType_LPARN:
        printf("{ %d:%d TokenType_LPARN }\n", _row, _colum);
        break;

    case TokenType_RPARN:
        printf("{ %d:%d TokenType_RPARN }\n", _row, _colum);
        break;

    case TokenType_LIST:
        printf("{ %d:%d TokenType_LIST }\n", _row, _colum);
        break;

    case TokenType_CONS:
        printf("{ %d:%d TokenType_CONS }\n", _row, _colum);
        break;

    case TokenType_EOF:
        printf("{ %d:%d TokenType_EOF }\n", _row, _colum);
        break;

    default:
        break;
    }
}

TokenList *TokenList_new(void)
{
    TokenList *list;

    if ((list = calloc(1, sizeof(TokenList))) == NULL)
        goto cleanup;

    list->length = 0;
    list->head = NULL;
    list->last = NULL;

    return list;

cleanup:
    if (list != NULL)
        free(list);

    return NULL;
}

void TokenList_delete(TokenList *list)
{
    TokenNode *iter = list->head;

    while (iter != NULL)
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
    if ((node = TokenNode_new(token.type, token.value, metadata)) == NULL)
        goto cleanup;

    if (list->head == NULL)
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
    if (node != NULL)
        TokenNode_delete(node);

    return 0;
}

int TokenList_remove(TokenList *list, Token token)
{
    TokenNode *iter = list->head;
    TokenNode *prev = NULL;

    while (iter != NULL)
    {
        if (memcmp(&(iter->token), &token, sizeof(Token)) == 0)
        {
            if (prev == NULL)
            {
                list->head = iter->next;
            }
            else if (iter == list->last)
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