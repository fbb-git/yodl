#include "yodl.h"

void gram_DOSUBST()
{
    int value;

    parser_push_fun("DOSUBST");

    if (parser_number_parlist(&parser, &value, false) == SUCCESS)
        parser_useSubst(&parser, value);

    parser_pop_fun();
}

/*
    DOSUBST(1) (the default) applies SUBSTs' values. 
    DOSUBST(0) applies SUBSTs' keys. 
*/
    



