#include "args.h"
#include "error.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void init_arg(arg_ctx_t *ctx)
{
  ctx->count = 0;
}

void register_arg(arg_ctx_t *ctx, arg_t arg)
{
  if (ctx->count < MAX_ARGS)
  {
    ctx->args[ctx->count++] = arg;
  }
  else
  {
    throw_err(__func__, __FILE__, __LINE__, "Cannot register more arguments, max limit reached.\n");
  }
}

int process_args(arg_ctx_t *ctx, int argc, char **argv)
{
  int has_initialized = 0;

  for (int i = 1; i < argc; ++i)
  {
    if (argv[i][0] == '-' && (argv[i][1] != '\0' && argv[i][1] != '-')) // Handles '-'
    {
      char *arg_name = argv[i] + 1;
      for (int j = 0; j < ctx->count; ++j)
      {
        if (ctx->args[j].short_name == *arg_name)
        {
          if (ctx->args[j].only_this)
          {
            for (int k = 1; k < argc; ++k)
            {
              if (k != i && argv[k][0] == '-' && (argv[k][1] != '\0' && argv[k][1] != *arg_name))
              {
                throw_err(__func__, __FILE__, __LINE__, "Argument %c should be the only argument provided.\n", *arg_name);
                return 1;
              }
            }
          }
          if (ctx->args[j].only_once)
          {
            for (int k = 1; k < argc; ++k)
            {
              if (k != i && argv[k][0] == '-' && (argv[k][1] != '\0' && argv[k][1] == *arg_name))
              {
                throw_err(__func__, __FILE__, __LINE__, "Argument %c can only be used once.\n", *arg_name);
                return 1;
              }
            }
          }
          if (ctx->args[j].requires_value)
          {
            if (i + 1 < argc && argv[i + 1][0] != '-')
            {
              if (ctx->args[j].handler(argv[i + 1]) == 0)
              {
                ++i;
              }
            }
            else
            {
              throw_err(__func__, __FILE__, __LINE__, "Argument %c requires a parameter.\n", *arg_name);
              return 1;
            }
          }
          else
          {
            if (ctx->args[j].handler(NULL) == 0)
            {
              ++i;
            }
          }
          if (ctx->args[j].only_this && !has_initialized)
          {
            has_initialized = 1;
          }
        }
      }
    }
    else if (argv[i][0] == '-' && argv[i][1] == '-')
    {
      char *arg_name = argv[i] + 2;
      for (int j = 0; j < ctx->count; ++j)
      {
        if (strcmp(ctx->args[j].long_name, arg_name) == 0)
        {
          if (ctx->args[j].only_this)
          {
            for (int k = 1; k < argc; ++k)
            {
              if (k != i && argv[k][0] == '-' && (argv[k][1] != '\0' && strcmp(argv[k] + 2, arg_name) != 0))
              {
                throw_err(__func__, __FILE__, __LINE__, "Argument %s should be the only argument provided.\n", arg_name);
                return 1;
              }
            }
          }
          if (ctx->args[j].only_once)
          {
            for (int k = 1; k < argc; ++k)
            {
              if (k != i && argv[k][0] == '-' && (argv[k][1] != '\0' && strcmp(argv[k] + 2, arg_name) == 0))
              {
                throw_err(__func__, __FILE__, __LINE__, "Argument %s can only be used once.\n", arg_name);
                return 1;
              }
            }
          }
          if (ctx->args[j].requires_value)
          {
            if (i + 1 < argc && argv[i + 1][0] != '-')
            {
              if (ctx->args[j].handler(argv[i + 1]) == 0)
              {
                ++i;
              }
            }
            else
            {
              throw_err(__func__, __FILE__, __LINE__, "Argument %s requires a parameter.\n", arg_name);
              return 1;
            }
          }
          else
          {
            if (ctx->args[j].handler(NULL) == 0)
            {
              ++i;
            }
          }
          if (ctx->args[j].only_this && !has_initialized)
          {
            has_initialized = 1;
          }
        }
      }
    }
  }
  return 0;
}
