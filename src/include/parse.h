#ifndef __PARSE_H
#define __PARSE_H


#include <vector.h>


struct __Node;

typedef enum __NodeType {
  NodeType_LIST,
  NodeType_INTEGER,
  NodeType_FLOAT,
  NodeType_SYMBOL,
  NodeType_STRING,
  NodeType_EOF,
  NodeType_DOT,
} NodeType;

typedef struct __NodeMetadata {
  int line;
  int column;
  int tokenStringLength;
} NodeMetadata;

typedef struct __NodeData {
  union {
    struct __List {
      struct __Node* car;
      struct __Node* cdr;
    } list;
    int intData;
    double doubleData;
    char* symbol;
    char* string;
  };
} NodeData;

typedef struct __Node {
  NodeType nodeType;
  NodeMetadata nodeMetadata;
  struct __Node* parent;
  Vector* children;
  NodeData* nodeData;
} ASTNode;


void Parser_init(void);
ASTNode* Parser_parseExpression(void);

bool Parser_isEOFNode(ASTNode* node);


#endif