#include "yodl.h"

void set_message_level()
{
    char const *arg = args_multiarg('v');

    while (arg != PFAILED)
    {
        message_incseverity();
        arg = args_multiarg(0);
    }

    arg = args_multiarg('m');
    while (arg != PFAILED)
    {
        message_optarg(arg);
        arg = args_multiarg(0);
    }
}
