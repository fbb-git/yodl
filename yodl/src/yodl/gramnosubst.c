#include "yodl.h"

/*
    NOTRANS():  macros are not expanded (except for CHAR())
                no CHARTABLE() is active.
*/

void gram_NOSUBST()
{
    parser_push_fun("NOTRANS");

//    lexer_setSubst(&parser.d_lexer, parser.d_emptySubst);

    lexer_lex(&parser.d_lexer);
    
    lexer_push_str(&parser.d_lexer, "(__");

    gram_NOTRANS();

    lexer_push_str(&parser.d_lexer, "__");

//    lexer_setSubst(&parser.d_lexer, parser.d_subst);


    parser_pop_fun();
}
