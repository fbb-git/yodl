#include "yodl.h"

/*
    STRLEN(src) inserts src's length into the lexical scanner
*/
    
void gram_STRLEN()
{
    register char *src;
    char length[50] = "0";

    parser_push_fun("STRLEN");              /* call STRLEN */

    src = parser_parlist(&parser, COLLECT_SET);     /* src contents */
    if (src != PFAILED)
        sprintf(length, "%lu", strlen(src));

    lexer_push_str(&parser.d_lexer, length);
    free(src);
    parser_pop_fun();
}



