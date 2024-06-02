#include <stdio.h>

int main(int argc, char**argv) {
  if(argc < 2) {
    printf("[Ark] Usage: %s <command> [args]!\n");
    return 1;
  }

  printf("{");
  for(int i = 0; i < argc; i++) {
    if(i != argc)
      printf("\"%s\", ", argv[i]);
    else
      printf(""\%s\"", argv[i]);
  }
  printf("}\n");
  return 0;
}
