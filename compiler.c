#include <stdio.h>
#include <stdlib.h>

#include "chunk.h"
#include "common.h"
#include "compiler.h"
#include "scanner.h"

typedef struct {
  Token current;
  Token previous;
  bool hadError;
  bool panicMode;
} Parser;

Parser parser;

static void errorAt(Token * token, const char * message) {
  if(parser.panicMode) return;
  parser.panicMode = true;
  fprintf(stderr, "[line %d] Error", token->line);
  if(token->line == TOKEN_EOF) {
    fprintf(stderr, "at end");
  } else if(token->type == ERROR) {
    
  } else {
    fprintf(stderr, "at '%.*s'", token->length, token->start);
  }

  fprintf(stderr, "%s\n", message);
  parser.hadError = true;
}
static void error(const char *message) {
  errorAt(&parser.previous, message);
}

static void errorAtCurrent(const char*message) {
  errorAt(&parser.current, message);
}

static void advance() {
  parser.previous = parser.current;

  for(;;) {
    parser.current = scanToke();
    if(parser.current.type != ERROR) break;

    errorAtCurrent(parser.current.start);
  }
}

static void expression() {

}

static void  consume(TokenType type, const char* message) {
  if(parser.current.type == type) {
    advance();
    return;
  }

  errorAtCurrent(message);
}

bool compile(const char *source, Chunk * chunk) {
  initScanner(source);
  parser.hadError = false;
  parser.panicMode = false;
  advance();
  expression();
  consume(TOKEN_EOF, "Expect end of expression.");
  return !parser.hadError;
}
