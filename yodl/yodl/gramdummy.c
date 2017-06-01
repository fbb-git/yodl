#include "yodl.h"

void gram_DUMMY()
{
    char *arg;

    parser_push_fun("DUMMY");
    arg = parser_parlist(&parser, COLLECT_SET);

    if (message_show(MSG_NOTICE))
        message("DUMMY(%s)", string_short(arg));

    parser_pop_fun();
    free (arg);
}
