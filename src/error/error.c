#include <error.h>
#include <vector.h>

#include <assert.h>
#include <string.h>
#include <stdlib.h>


static const char* const concatenator = ": ";
static Vector* errors;

ErrorDescription* ErrorDescription_new(int line, int column, char* message, char* what) {
  int concatenatorLength = strlen(concatenator);
  int messageLength = strlen(message);
  int whatLength = strlen(what);

  ErrorDescription* description = malloc(sizeof(ErrorDescription));
  char* errorString = malloc(sizeof(char) * (messageLength + concatenatorLength + whatLength));

  strncpy(errorString, message, messageLength);
  strncpy(errorString + messageLength, concatenator, concatenatorLength);
  strncpy(errorString + messageLength + concatenatorLength, what, whatLength);

  description->line = line;
  description->column = column;
  description->message = errorString;

  return description;
}

void ErrorDescription_delete(ErrorDescription** selfPointer) {
  ErrorDescription* self = *selfPointer;
  assert(self != NULL);
  assert(self->message != NULL);

  free(self->message);
  self->line = 0;
  self->column = 0;
  self->message = NULL;

  free(*selfPointer);
  *selfPointer = NULL;
}

void Error_init(void) {
  if (errors) {
    Vector_delete(&errors);
  }

  errors = Vector_new();
}

void Error_add(ErrorDescription* description) {
  Vector_pushBack(errors, description);
}

Vector* Error_getErrors(void) {
  return errors;
}

void Error_clear(void) {
  for (int i = 0; i < errors->size; i++) {
    ErrorDescription* description = Vector_get(errors, i);
    ErrorDescription_delete(&description);
  }
  
  Vector_delete(&errors);
}

bool Error_exists(void) {
  return Vector_empty(errors);
}