#include "help.h"
#include "../helpers/utils.h"
#include "../ark.h"

int help_handler(char *arg)
{
    (void)arg;
    usage(_argv);
    return 0;
}