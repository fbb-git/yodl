#include "yodl.h"

void gram_TYPEOUT()
{
    char *msg;

    parser_push_fun("TYPEOUT");

    msg = parser_parlist(&parser, COLLECT_SET);
    if (message_show(MSG_NOTICE))
        message("TYPEOUT %s", string_short(msg));
    msg = parser_nochartab_eval(&parser, msg);
    fprintf (stderr, "%s\n", msg);

    parser_pop_fun();
    free(msg);
}
