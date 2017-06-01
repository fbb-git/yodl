#include "yodl.h"

void gram_POPSUBST()
{
    parser_push_fun("POPSUBST");
    parser_empty_parlist(&parser);
    parser_popSubst(&parser);
    parser_pop_fun();
}

    



