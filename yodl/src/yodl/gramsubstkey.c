#include "yodl.h"

void gram_SUBSTKEY()
{
    parser_push_fun("SUBSTKEY");

    int value;
    if (parser_number_parlist(&parser, &value, false) == SUCCESS)
        parser_insertSubst(&parser, ptr->d_value);

    parser_pop_fun();
}
