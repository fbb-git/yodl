#include "yodl.h"

void gram_XXSUBST()
{
    parser_push_fun("XXSUBST");

    int value;
    if (parser_number_parlist(&parser, &value, false) == SUCCESS)
        parser_insertSubst(&parser, value);

    parser_pop_fun();
}

/* 
    Depending on the value of parser's d_useSubst data member either the
    XXSUBST's key or value is inserted into the lexer's media
*/
