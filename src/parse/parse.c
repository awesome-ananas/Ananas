#include <error.h>
#include <parse.h>

#include <ctype.h>
#include <stdbool.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>


static int line = 0;
static int column = 0;

static ASTNode* const EOF_NODE = &(ASTNode) {
  NodeType_EOF,
  (NodeMetadata) {
    0,
    0,
    0,
  },
  NULL,
  NULL,
  NULL,
};

static const char* const SYMBOL_SET = "~!@#$%^&*-_=+:/?<>";

static inline void increaseLine(void);
static inline void increaseColumn(void);
static inline void clearColumn(void);
static inline bool isLinuxNewline(int c);
static inline bool isWindowsNewline(int c);
static inline void consumeCarriageReturn(void);
static int peek();
static void skipLine();
static ASTNode* parseList(void);
static ASTNode* generateDotNode(void);

static void raiseUnexpectedTokenError(char* unexpected);


void Parser_init(void) {
  line = 0;
  column = 0;
}

ASTNode* Parser_parseExpression(void) {
  for (;;) {
    int c = getchar();
    
    if (isspace(c)) 
    {
      if (isWindowsNewline(c)) {
        consumeCarriageReturn();
        clearColumn();
        increaseLine();
      } else if (isLinuxNewline(c)) {
        clearColumn();
        increaseLine();
      } else {
        increaseColumn();
      }
    } 
    else if (c == EOF) 
    {
      return EOF_NODE;
    } 
    else if (c == ';') 
    {
      skipLine();
    } 
    else if (c == '(') 
    {
      return parseList();
    } 
    else if (c == ')') 
    {
      raiseUnexpectedTokenError(")");
    } 
    else if (c == '.') 
    {
      return generateDotNode();
    } 
    else if (c == '\'') 
    {

    } 
    else if (isdigit(c)) 
    {

    } 
    else if (c == '-' && isdigit(peek())) 
    {

    } 
    else if (isalpha(c) || strchr(SYMBOL_SET, c)) 
    {

    } 
    else 
    {

    }
  }
}

bool Parser_isEOFNode(ASTNode* node) {
  return node == EOF_NODE;
}

static inline void increaseLine() {
  line++;
}

static inline void increaseColumn() {
  column++;
}

static inline void clearColumn() {
  column = 0;
}

static inline bool isLinuxNewline(int c) {
  return c == '\n';
}

static inline bool isWindowsNewline(int c) {
  int nextChar = peek();
  
  return c == '\n' && nextChar == '\r';
}

static inline void consumeCarriageReturn(void) {
  getchar();
}

static int peek() {
  int c = getchar();
  ungetc(c, stdin);

  return c;
}

static void skipLine() {
  for (;;) {
    int next = getchar();
    
    if (isLinuxNewline(next) || isWindowsNewline(next)) {
      clearColumn();
      increaseLine();

      break;
    }

    increaseColumn();
  }
}

static ASTNode* parseList(void) {
  // TODO: implementation
  return NULL;
}

static ASTNode* generateDotNode(void) {
  ASTNode* generatedNode = malloc(sizeof(ASTNode));
  ASTNode originalNode = (ASTNode) {
    NodeType_DOT,
    (NodeMetadata) {
      line,
      column,
      1,
    },
    NULL,
    NULL,
    NULL,
  };
  memcpy(generatedNode, &originalNode, sizeof(ASTNode));

  return generatedNode;
}

static void raiseUnexpectedTokenError(char* unexpected) {
  ErrorDescription* description = ErrorDescription_new(line, column, "Unexpected token", unexpected);
  Error_add(description);
}