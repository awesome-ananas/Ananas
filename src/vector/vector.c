#include <vector.h>

#include <memory.h>
#include <stdlib.h>
#include <stdbool.h>


static const int VECTOR_INIT_SIZE = 16;
static const int VECTOR_EXPAND_FACTOR = 2;

static inline bool hasEnoughSpace(Vector* self);
static void expandVector(Vector* self);
static void pushBackChecked(Vector* self, void* object);
static inline bool accessibleIndex(Vector* self, int index);
static void* getChecked(Vector* self, int index);

Vector* Vector_new(void) {
  Vector* vector = malloc(sizeof(Vector));
  vector->buffer = malloc(sizeof(void*) * VECTOR_INIT_SIZE);
  vector->size = 0;
  vector->capacity = VECTOR_INIT_SIZE;

  return vector;
}

void Vector_delete(Vector* self) {
  assert(self->buffer != NULL);

  free(self->buffer);
  self->buffer = NULL;
  self->size = 0;
  self->capacity = 0;
}

void Vector_pushBack(Vector* self, void* object) {
  if (!hasEnoughSpace(self)) {
    expandVector(self);
  }

  pushBackChecked(self, object);
}

void* Vector_get(Vector* self, int index) {
  if (accessibleIndex(self, index)) {
    return getChecked(self, index);
  }

  return NULL;
}

static inline bool hasEnoughSpace(Vector* self) {
  return self->size < self->capacity;
}

static void expandVector(Vector* self) {
  int oldCapacity = self->capacity;
  int oldSize = self->size;
  void** oldBuffer = self->buffer;
  int newCapacity = oldCapacity * VECTOR_EXPAND_FACTOR;
  int newSize = oldSize;
  void** newBuffer = malloc(sizeof(void*) * newCapacity);

  memcpy(newBuffer, oldBuffer, sizeof(void*) * oldSize);

  self->buffer = newBuffer;
  self->capacity = newCapacity;
}

static void pushBackChecked(Vector* self, void* object) {
  int insertionIndex = self->size;
  void** buffer = self->buffer;

  buffer[insertionIndex] = object;
  
  self->size++;
}

static inline bool accessibleIndex(Vector* self, int index) {
  return index < self->size && index >= 0;
}

static void* getChecked(Vector* self, int index) {
  return self->buffer[index];
}
