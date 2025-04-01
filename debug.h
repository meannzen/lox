#ifndef lox_debug_h
#define lox_debug_h

#include "chunk.h"
#include "value.h"

void disassembleChunk(Chunk* chunk, const char*name);
int disassembleInstruction(Chunk* chunk, int offset);
#endif
