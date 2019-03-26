#ifndef __ERROR_H
#define __ERROR_H

#include <stdbool.h>


typedef struct __Vector Vector;

typedef struct __ErrorDescription {
  int line;
  int column;
  char* message;
} ErrorDescription;

ErrorDescription* ErrorDescription_new(int line, int column, char* message, char* what);
void ErrorDescription_delete(ErrorDescription** selfPointer);

void Error_init(void);
void Error_add(ErrorDescription* description);
Vector* Error_getErrors(void);
void Error_clear(void);
bool Error_exists(void);


#endif