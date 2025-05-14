#include "vm.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static void repl() {
  char line[1024];
  for(;;) {
    printf(">");
    if(!fgets(line, sizeof(line), stdin)) {
      printf("\n");
      break;
    }

   printf("%s", line); }
}

int main(int argc, const char *argv[]) {
  initVM();
  if(argc == 1) {
    repl();
  } else if(argc == 2) {
    // file inputed
  } else {
    fprintf(stderr,"Usage: lox [path]\n");
    exit(64);
  }
  freeVM();
  return 0;
}
