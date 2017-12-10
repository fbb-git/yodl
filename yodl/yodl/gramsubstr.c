#include "yodl.h"

/*
    SUBSTR(srctext)(offset)(length) inserts substr into the lexical scanner
*/
    
void gram_SUBSTR()
{
    register char *src;
    int offset;
    int length;

    parser_push_fun("SUBSTR");              /* call SUBSTR */

    src = parser_parlist(&parser, COLLECT_SET);     /* src contents */
    if (src == PFAILED)
    {
        if (message_show(MSG_WARNING))
            message("%s: empty string", parser_fun());
        return;
    }

    if (parser_number_parlist(&parser, &offset, true) == FAILED)
        offset = 0;
    if (parser_number_parlist(&parser, &length, false) == FAILED)
        length = INT_MAX;

    String *str = string_move(src);

    src = string_substr(str, offset, length);
    lexer_push_str(&parser.d_lexer, src);
    free(src);

    string_delete(&str);

    parser_pop_fun();
}



