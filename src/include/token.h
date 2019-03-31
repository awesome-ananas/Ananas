#ifndef __TOKEN_H
#define __TOKEN_H

#define MAX_STRING (0xFF)
#define MAX_SYMBOL (0xFF)

typedef enum __TokenType
{
    TokenType_INTEGER,
    TokenType_FLOATING,
    TokenType_STRING,
    TokenType_SYMBOL,
    TokenType_BOOLEAN, /* #t #f */
    TokenType_LPARN, /* ( */
    TokenType_RPARN, /* ) */
    TokenType_CONS,  /* : */
    TokenType_LIST,  /* ' */
    TokenType_EOF
} TokenType;

typedef union __TokenValue {
    int integer;
    int boolean;
    double floating;
    char string[MAX_STRING];
    char symbol[MAX_SYMBOL];
} TokenValue;

typedef struct __Token
{
    TokenType type;
    TokenValue value;
} Token;

#endif