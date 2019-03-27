#include <parse.h>
#include <util.h>

#include <assert.h>
#include <stddef.h>

NodeMetadata* NodeMetadata_new(int line, int column, int tokenStringLength) {
  NodeMetadata* nodeMetadata = malloc(sizeof(NodeMetadata));
  nodeMetadata->line = line;
  nodeMetadata->column = column;
  nodeMetadata->tokenStringLength = tokenStringLength;

  return nodeMetadata;
}

void NodeMetadata_delete(NodeMetadata** selfPointer) {
  NodeMetadata* self = *selfPointer;
  assert(self != NULL);
  
  self->line = 0;
  self->column = 0;
  self->tokenStringLength = 0;

  freeSelfPointer((void**) selfPointer);
}