#include <error.h>
#include <parse.h>
#include <stack.h>

#include <ctype.h>
#include <stdbool.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>


static int line = 0;
static int column = 0;

static ASTNode* const EOF_NODE = &(ASTNode) {
  NodeType_EOF,
  &(NodeMetadata) {
    0,
    0,
    0,
  },
  NULL,
  NULL,
};

static const int NUMBER_STRING_LENGTH = 256;
static const int DOT_LENGTH = 1;
static const char* const SYMBOL_SET = "~!@#$%^&*-_=+:/?<>";

static inline void increaseLine(int increasing);
static inline void increaseColumn(int increasing);
static inline void clearColumn(void);
static inline bool isLinuxNewline(int c);
static inline bool isWindowsNewline(int c);
static inline void consumeCarriageReturn(void);
static inline bool isNextFloatingPoint(void);
static int peek(void);
static void skipBlank(int blankCharacter);
static void skipLine(void);
static int getDigitCount(int number);
static ASTNode* parseList(void);
static ASTNode* parseNumber(void);
static int getIntegerPart(void);
static int getFloatingPointPart(void);
static ASTNode* generateNode(NodeType nodeType, NodeMetadata* metadata, NodeData* data);
static ASTNode* generateDot(void);
static ASTNode* generateInteger(int integerPart);
static ASTNode* generateFloatingPoint(int integerPart, int floatingPointPart);
static double twoIntegersToDouble(int integerPart, int floatingPointPart);

static void raiseUnexpectedTokenError(char* unexpected);


void Parser_init(void) {
  line = 0;
  column = 0;
}

void Parser_clear(void) {
  line = 0;
  column = 0;
}

ASTNode* Parser_parseExpression(void) {
  for (;;) {
    int c = getchar(); // TODO: peek로 변경하기
    
    if (isspace(c)) 
    {
      skipBlank(c);
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
      increaseColumn(1);
      raiseUnexpectedTokenError(")");
    } 
    else if (c == '.') 
    {
      increaseColumn(1);
      return generateDot();
    } 
    else if (c == '\'') 
    {

    } 
    else if (isdigit(c)) 
    {
      ungetc(c, stdin);
      
      return parseNumber();
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

static inline void increaseLine(int increasing) {
  line += increasing;
}

static inline void increaseColumn(int increasing) {
  column += increasing;
}

static inline void clearColumn() {
  column = 0;
}

static inline bool isLinuxNewline(int c) {
  return c == '\n';
}

static inline bool isWindowsNewline(int c) {
  int nextChar = peek();
  
  return c == '\r' && nextChar == '\n';
}

static inline void consumeCarriageReturn(void) {
  getchar();
}

static inline bool isNextFloatingPoint(void) {
  return peek() == '.';
}

static int peek(void) {
  int c = getchar();
  ungetc(c, stdin);

  return c;
}

static void skipBlank(int blankCharacter) {
  if (isWindowsNewline(blankCharacter)) {
    consumeCarriageReturn(); // TODO: 이름 바꾸기
    clearColumn();
    increaseLine(1);
  } else if (isLinuxNewline(blankCharacter)) {
    clearColumn();
    increaseLine(1);
  } else {
    increaseColumn(1);
  }
}

static void skipLine(void) {
  for (;;) {
    int next = getchar();
    
    if (isLinuxNewline(next) || isWindowsNewline(next)) {
      clearColumn();
      increaseLine(1);

      break;
    }

    increaseColumn(1);
  }
}

static int getDigitCount(int number) {
  int count = 0; 
  while (number != 0) { 
    number /= 10; 
    ++count; 
  } 
  
  return count; 
}

static ASTNode* parseList(void) {
  // TODO: implementation
  return NULL;
}

static ASTNode* parseNumber(void) {
  int integerPart = getIntegerPart();
  if (isNextFloatingPoint())
  {
    getchar();
    int floatingPointPart = getFloatingPointPart();

    return generateFloatingPoint(integerPart, floatingPointPart);
  } 
  else 
  {
    return generateInteger(integerPart);
  }
}

static int getIntegerPart(void) {
  int c;
  char numberBuffer[NUMBER_STRING_LENGTH] = { 0, };
  int index = 0;
  do 
  {
    c = getchar();
    numberBuffer[index] = c;

    index++;
  } 
  while (isdigit(peek()));
  int length = index;
  int number = strtol(numberBuffer, numberBuffer + length, 10);

  increaseColumn(length);

  return number;
}

static int getFloatingPointPart(void) {
  return getIntegerPart();
}

static ASTNode* generateNode(NodeType nodeType, NodeMetadata* metadata, NodeData* data) {
  ASTNode* generatedNode = malloc(sizeof(ASTNode));
  ASTNode originalNode = (ASTNode) {
    nodeType,
    metadata,
    Vector_new(),
    data
  };
  memcpy(generatedNode, &originalNode, sizeof(ASTNode));

  return generatedNode;
}

static ASTNode* generateDot(void) {
  ASTNode* generatedNode = malloc(sizeof(ASTNode));
  NodeData* nodeData = malloc(sizeof(NodeData));
  NodeMetadata* metadata = NodeMetadata_new(line, column, DOT_LENGTH);

  nodeData->symbol = ".";

  return generateNode(NodeType_DOT, metadata, nodeData);
}

static ASTNode* generateInteger(int integerPart) {
  NodeData* nodeData = malloc(sizeof(NodeData));
  NodeMetadata* metadata = NodeMetadata_new(line, column, getDigitCount(integerPart));

  nodeData->intData = integerPart;

  return generateNode(NodeType_INTEGER, metadata, nodeData);
}

static ASTNode* generateFloatingPoint(int integerPart, int floatingPointPart) {
  int tokenStringLength = getDigitCount(integerPart) + DOT_LENGTH + getDigitCount(floatingPointPart);
  NodeData* nodeData = malloc(sizeof(NodeData));
  NodeMetadata* metadata = NodeMetadata_new(line, column, tokenStringLength);

  nodeData->doubleData = twoIntegersToDouble(integerPart, floatingPointPart);

  return generateNode(NodeType_FLOAT, metadata, nodeData);
}

static double twoIntegersToDouble(int integerPart, int floatingPointPart) {
  char buffer[NUMBER_STRING_LENGTH * 2 + DOT_LENGTH];
  int integerPartLength = getDigitCount(integerPart);
  int floatingPointPartLength = getDigitCount(floatingPointPart);
  int fullLength = integerPartLength + DOT_LENGTH + floatingPointPartLength;

  sprintf(buffer, "%d.%d", integerPart, floatingPointPart);

  return strtod(buffer, NULL);
}

static void raiseUnexpectedTokenError(char* unexpected) {
  ErrorDescription* description = ErrorDescription_new(line, column, "Unexpected token", unexpected);
  Error_add(description);
}