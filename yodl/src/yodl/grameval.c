#include "yodl.h"

void gram_EVAL()
{
    register char *arg;

    parser_push_fun("EVAL");

    arg = parser_parlist(&parser, COLLECT_SET);             /* get the list */
    if (message_show(MSG_NOTICE))
        message("EVAL(%s)", string_short(arg));
    arg = parser_eval(&parser, arg);                        /* evaluate it  */

    lexer_push_str(&parser.d_lexer, arg);                   /* parse the    */
                                                            /* evaluation   */
    free(arg);
    parser_pop_fun();
}
