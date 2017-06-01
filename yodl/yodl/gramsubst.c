#include "yodl.h"

void gram_SUBST()
{
    char *key;
    char *value;

    parser_push_fun("SUBST");

    key   = parser_parlist(&parser, COLLECT_SET);
    parser_skipws(&parser);
    value = parser_parlist(&parser, COLLECT_SET);

    subst_insert(&parser.d_subst, "SUBST", key, value);

    parser_pop_fun();
    free (value);
    free (key);
}
