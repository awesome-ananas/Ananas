#include <error.h>
#include <parse.h>

#include <stdio.h>

void init(void);
void quit(void);

int main(void) {
  init();

  for (;;) {
    Error_init();
    ASTNode* node = Parser_parseExpression();
    if (Parser_isEOFNode(node)) {
      break;
    }
    Error_clear();
  }

  quit();
  
  return 0;
}

void init(void) {
  Parser_init();
}

void quit(void) {
  Error_clear();
}
