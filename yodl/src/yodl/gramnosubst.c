#include "yodl.h"

/*
    NOTRANS():  macros are not expanded (except for CHAR())
                no CHARTABLE() is active.
*/

void gram_NOSUBST()
{
    parser_push_fun("NOSUBST");

    lexer_setSubst(&parser.d_lexer, parser.d_emptySubst);

    gram_NOTRANS();

    lexer_setSubst(&parser.d_lexer, parser.d_subst);


    parser_pop_fun();
}
