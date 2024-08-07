#include <stdio.h>
#include <stdlib.h>

#ifdef __linux__
#include <readline/readline.h>
#include <readline/history.h>

int main(int argc, char *argv[]) {

  puts("Lipur Version 0.0.1");
  puts("Press Ctrl+C to Exit\n");

  for(;;) {
    char *input = readline("lipur> ");

    add_history(input);

    printf("You are %s\n", input);

    free(input);
  }

  return 0;
}

#else
#error "OS not supported"
#endif
