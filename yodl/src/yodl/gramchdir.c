#include "yodl.h"

void gram_CHDIR()
{
    char *arg;

    parser_push_fun("CHDIR");

    arg = parser_parlist(&parser, COLLECT_SET);

    if (chdir(arg) && message_show(MSG_ERR))
        message("CHDIR %s: %s", arg, strerror(errno));
    else if (message_show(MSG_NOTICE))
        message("CHDIR: %s", string_short(arg));


    parser_pop_fun();
    free (arg);
}
