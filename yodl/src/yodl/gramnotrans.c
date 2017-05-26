#include "yodl.h"

/*
    NOTRANS():  macros are not expanded (except for CHAR())
                no CHARTABLE() is active.
*/

void gram_NOTRANS()
{
//    char *arg;

    parser_push_fun("NOTRANS");

//    arg = parser_parlist(&parser, COLLECT_SET);
//    message(__FILE__ ": %s", arg);

//    parser_allow_subst(&parser, false);
//    arg = parser_evalSet(&parser, arg, NOTRANS_SET);
//    parser_allow_subst(&parser, true);
//    free(arg);

    gram_NOEXPAND();
    parser_pop_fun();
}
