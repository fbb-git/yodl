#include "yodl.h"

void gram_ERROR()
{
    char *arg;

    parser_push_fun("ERROR");

    arg = parser_nochartab_eval(&parser,
                                parser_parlist(&parser, COLLECT_SET));

    if (message_show(MSG_CRIT))
        message("ERROR: %s", arg);

    parser_pop_fun();
    free(arg);
}
