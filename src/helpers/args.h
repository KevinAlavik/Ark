#ifndef ARGS_H
#define ARGS_H

#include <stdbool.h>

#define MAX_ARGS 10
#define MAX_ARG_LENGTH 50

typedef struct
{
  char long_name[MAX_ARG_LENGTH];
  char short_name;
  char description[MAX_ARG_LENGTH];
  int (*handler)(char *);
  bool requires_value;
  bool can_be_added_more_than_once;
  bool only_once;
  bool only_this;
} arg_t;

typedef struct
{
  arg_t args[MAX_ARGS];
  int count;
} arg_ctx_t;

void init_arg(arg_ctx_t *ctx);
void register_arg(arg_ctx_t *ctx, arg_t arg);
int process_args(arg_ctx_t *ctx, int argc, char **argv);

#endif /* ARGS_H */
