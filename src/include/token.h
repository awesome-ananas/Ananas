#ifndef __TOKEN_H
#define __TOKEN_H

typedef enum __TokenType
{
    TokenType_INTEGER,
    TokenType_FLOATING,
    TokenType_STRING,
    TokenType_SYMBOL,
    TokenType_LPARN, /* ( */
    TokenType_RPARN, /* ) */
    TokenType_CONS, /* : */
    TokenType_COMMENT, /* ; */
    TokenType_LIST /* ' */
} TokenType;

typedef union __TokenValue
{
    int integer;
    double floating;
    char *string;
    char *symbol;
    char *comment;
} TokenValue;

typedef struct __Token
{
    TokenType type;
    TokenValue value;
} Token;

#endif