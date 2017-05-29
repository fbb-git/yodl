#include "yodl.h"

/*
    NOTRANS():  macros are not expanded (except for CHAR())
                no CHARTABLE() is active.
*/

void gram_NOTRANS()
{
    parser_push_fun("NOTRANS");
    gram_NOEXPAND();
    parser_pop_fun();
}
