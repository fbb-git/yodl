#include "yodl.h"

void gram_PUSHSUBST()
{
    int value;

    parser_push_fun("PUSHSUBST");

    if (parser_number_parlist(&parser, &value, false) == SUCCESS)
        parser_pushSubst(&parser, value);

    parser_pop_fun();
}

/*
    PUSHSUBST(1) applies SUBSTs' values. 
    PUSHSUBST(0) applies SUBSTs' keys. 
*/
    



