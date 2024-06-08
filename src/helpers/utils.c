#include "utils.h"

#include <stdio.h>

void usage(char **argv)
{
    printf("Usage: %s [OPTION]...\n", argv[0]);
    printf("Ark: A Codesign framework for signing iOS applications.\n\n");
    printf("Options:\n");
    printf("  -h,   --help                                          display this help and exit\n\n");
}