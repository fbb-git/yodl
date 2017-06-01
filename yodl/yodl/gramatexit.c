
#include "yodl.h"

void gram_ATEXIT ()
{
    char *text;

    parser_push_fun("ATEXIT");
    text  = parser_parlist(&parser, COLLECT_SET);

    if (message_show(MSG_NOTICE))
        message("ATEXIT %s",  string_short(text));

    parser_atexit(&parser, text);                   /* consumes text no     */
                                                    /* need to free(text)   */
    parser_pop_fun();
}
