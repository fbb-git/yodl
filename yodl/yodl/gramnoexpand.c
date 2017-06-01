#include "yodl.h"

/*
    NOEXPAND(): macros are not expanded.
                CHARTABLE() remains active
    NOTRANS(): macros are not expanded,
                CHARTABLE() suppressed.
*/

void gram_NOEXPAND()
{
    bool noexpand;

    if ((noexpand = strcmp(parser_fun(), "NOTRANS")))
        parser_push_fun("NOEXPAND");

    parser_parlist(&parser, noexpand ? NOEXPAND_SET : NOTRANS_SET);
    if (message_show(MSG_NOTICE))
        message("%s(...)", parser_fun());

    if (noexpand)
        parser_pop_fun();
}
