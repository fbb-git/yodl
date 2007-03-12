#include "yodl.h"

void gram_WARNING()
{
    char *msg;

    parser_push_fun("WARNING");

    warning
    (
        "WARNING: %s",
            msg = parser_nochartab_eval(&parser,
                                        parser_parlist(&parser, COLLECT_SET))
    );

    parser_pop_fun();
    free(msg);
}
