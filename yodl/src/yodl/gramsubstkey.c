#include "yodl.h"

void gram_SUBSTKEY()
{
    parser_push_fun("SUBSTKEY");

    int value;
    if (parser_number_parlist(&parser, &value, false) == SUCCESS)
        parser_insertSubst(&parser, value);

    parser_pop_fun();
}

/* 
    Depending on the value of parser's d_useSubst data member either the
    SUBSTKEY's key or value is inserted into the lexer's media
*/
