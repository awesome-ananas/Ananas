#include <util.h>

#include <stdlib.h>


void freeSelfPointer(void** selfPointer) {
  free(*selfPointer);
  *selfPointer = NULL;
}
