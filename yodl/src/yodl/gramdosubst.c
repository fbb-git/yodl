#include "yodl.h"

void gram_DOSUBST()
{
    register char *arg;
    int value;

    parser_push_fun("DOSUBST");

    if (parser_number_parlist(&parser, &value, false) == SUCCESS)
        parser_useSubst(value);

    parser_pop_fun();

    free(arg);
}





