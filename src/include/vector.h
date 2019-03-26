#ifndef __VECTOR_H
#define __VECTOR_H

#include <stdbool.h>


typedef struct __Vector {
  void** buffer;
  int size;
  int capacity;
} Vector;

Vector* Vector_new(void);
void Vector_delete(Vector** selfPointer);
void Vector_pushBack(Vector* self, void* object);
void* Vector_get(Vector* self, int index);
bool Vector_empty(Vector* self);

#endif