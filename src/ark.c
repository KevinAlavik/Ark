#include <stdio.h>
#include <stdlib.h>
#include "helpers/error.h"
#include "helpers/args.h"
#include "helpers/utils.h"
#include "commands/help.h"
#include <string.h>

char **_argv;

int main(int argc, char **argv)
{
	_argv = argv;
	int argr = 1;
	arg_ctx_t *arg_ctx = (arg_ctx_t *)malloc(sizeof(arg_ctx_t));
	init_arg(arg_ctx);

	if (argc < 2)
	{
		usage(_argv);
		return 1;
	}

	arg_t help_arg = {
		"help",
		'h',
		"Displays help.",
		help_handler,
		false,
		false,
		true,
		false,
	};
	register_arg(arg_ctx, help_arg);
	argr++;

	if (process_args(arg_ctx, argc, argv))
	{
		throw_err(__func__, __FILE__, __LINE__, "Invalid command line arguments.\n");
		usage(_argv);
		return 1;
	}

	if (argr == argc || argr < argc)
	{
		for (int i = (argr == argc ? argr - 1 : argr); i < argc; i++)
		{
			if (argv[i][0] == '-')
			{
				if ((strcmp(argv[i] + 1, "h") != 0) && (strcmp(argv[i] + 1, "-help") != 0))
				{
					throw_err(__func__, __FILE__, __LINE__, "Unknown command line argument: \"%s\".\n", argv[i]);
					usage(_argv);
					return 1;
				}
			}
		}
	}

	return 0;
}
