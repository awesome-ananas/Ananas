#ifndef __VECTOR_H
#define __VECTOR_H


typedef struct __Vector {
  void** buffer;
  int size;
  int capacity;
} Vector;

Vector* Vector_new(void);
void Vector_delete(Vector* self);
void Vector_pushBack(Vector* self, void* object);
void* Vector_get(Vector* self, int index);

#endif