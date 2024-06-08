#include "error.h"

void throw_err(const char *func, const char *file, const int line, const char *format, ...)
{
    va_list args;
    va_start(args, format);

#ifdef VERBOSE
    fprintf(stderr, "[" ANSI_COLOR_RED "ERROR" ANSI_COLOR_RESET " @ %s:%d (%s)] ", file, line, func);
    vfprintf(stderr, format, args);
    fprintf(stderr, "\n");
#else
    fprintf(stderr, "[" ANSI_COLOR_RED "ERROR" ANSI_COLOR_RESET "] ");
    vfprintf(stderr, format, args);
    fprintf(stderr, "\n");
#endif

    va_end(args);
    exit(EXIT_FAILURE);
}
