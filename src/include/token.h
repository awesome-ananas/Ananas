#ifndef __TOKEN_H
#define __TOKEN_H

typedef enum
{
    Tokentype_LPARN,
    Tokentype_RPARN,
    Tokentype_INTEGER,
    Tokentype_FLOATING,
    Tokentype_STRING,
    Tokentype_IDENT,
} Tokentype;

typedef union
{
    int integer;
    double floating;
    char *string;
    char *symbol;
} Literal;

typedef struct
{
    Tokentype type;
    Literal value;
} Token;

#endif