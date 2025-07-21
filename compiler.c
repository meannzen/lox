#include <stdint.h>
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

Chunk * compiling_chunk;

static Chunk * current_chunk() {
   return compiling_chunk;
}

static void error_at(Token * token, const char * message) {
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
  error_at(&parser.previous, message);
}

static void error_at_current(const char*message) {
  error_at(&parser.current, message);
}

static void advance() {
  parser.previous = parser.current;

  for(;;) {
    parser.current = scanToke();
    if(parser.current.type != ERROR) break;

    error_at_current(parser.current.start);
  }
}

static void expression() {

}

static void  consume(TokenType type, const char* message) {
  if(parser.current.type == type) {
    advance();
    return;
  }

  error_at_current(message);
}

static void emit_byte(uint8_t byte) {
   writeChunk(current_chunk(),  byte, parser.previous.line);
}

static void emit_bytes(uint8_t byte1, uint8_t byte2) {
   emit_byte(byte1);
   emit_byte(byte2);
}

static void emit_return() {
   emit_byte(OP_RETURN);
}

static void end_compiler() {
   emit_return();
}

bool compile(const char *source, Chunk * chunk) {
  initScanner(source);
  compiling_chunk = chunk;
  parser.hadError = false;
  parser.panicMode = false;
  advance();
  expression();
  consume(TOKEN_EOF, "Expect end of expression.");
  end_compiler();
  return !parser.hadError;
}
