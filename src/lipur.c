#ifdef __linux__
#include <stdio.h>
#include <stdlib.h>
#include "mpc.h"

#include <readline/readline.h>
#include <readline/history.h>
/* or your distro libraries (NixOS is mine) */

typedef struct mpc_ast_t {
  char *tag;
  char *contents;
  mpc_state_t state;
  int children_num;
  struct mpc_ast_t **children;
} mpc_ast_t;

int 
main(int argc, char *argv[])
{
  mpc_parser_t *Number   = mpc_new("number");
  mpc_parser_t *Operator = mpc_new("operator");
  mpc_parser_t *Expr     = mpc_new("expr");
  mpc_parser_t *Lipur    = mpc_new("lipur");

  mpca_lang(MPCA_LANG_DEFAULT,
    "                                                                       \
      number   : /-?[0-9]+/ ;                                               \
      operator : '+' | '-' | '*' | '/' ;                                    \
      expr     : <number> <operator> <number> | '('? <expr> ')'? <operator> '('? <expr> ')'? ; \
      lipur    : /^/ <expr> /$/ ;                                         \
    ",
    Number, Operator, Expr, Lipur);


  puts("Lipur Version 0.0.1");
  puts("Press Ctrl+C to Exit\n");

  for (;;) {
    char *input = readline("lipur> ");
    add_history(input);

    mpc_result_t r;
    if (mpc_parse("<stdin>", input, Lipur, &r)) {
      mpc_ast_print(r.output);
      mpc_ast_delete(r.output);
    } else {
      mpc_err_print(r.error);
      mpc_err_delete(r.error);
    }

    free(input);
  }


  mpc_cleanup(4, Number, Operator, Expr, Lipur);
  return 0;
}

#else
#error "OS not supported"
#endif
