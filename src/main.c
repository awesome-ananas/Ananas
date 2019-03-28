#include <error.h>
#include <parse.h>

#include <stdio.h>

void init(void);
void quit(void);

int main(void) { /* REPL */
  init();

  for (;;) {
    Error_init();
    ASTNode* node = Parser_parseExpression();
    if (Parser_isEOFNode(node)) {
      break;
    } else {
      printf("Node received: %d\n", node->nodeType);
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
  Parser_clear();
  Error_clear();
}
