#ifndef __LEXER_C
#define __LEXER_C

typedef struct __Lexer
{

} Lexer;

Lexer *Lexer_new(void);
void Lexer_delete(Lexer *self);
void Lexer_lex(Lexer *self);

#endif