#include "yodl.h"

/*
    STRLEN(src) inserts src's length into the lexical scanner

    str can be a symbol name or literal text
*/
    
void gram_STRLEN()
{
    parser_push_fun("STRLEN");              // call STRLEN

                                            // src contents
    register char *src = parser_parlist(&parser, COLLECT_SET);     

    if (src != PFAILED)
    {
                                            // the symbol's or literal text
        char const *txt = parser_strvalue(&parser, src);
        char length[50] = "0";

        sprintf(length, "%lu", strlen(txt));

        lexer_push_str(&parser.d_lexer, length);
        free(src);
    }

    parser_pop_fun();
}



