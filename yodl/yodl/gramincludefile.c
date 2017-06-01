#include "yodl.h"

void gram_INCLUDEFILE()
{
    char *parlist;
    char const *filename;

    parser_push_fun("INCLUDEFILE");

    parlist = parser_parlist(&parser, COLLECT_SET);

    if (message_show(MSG_NOTICE))
        message("INCLUDEFILE `%s'", parlist);

    filename = parser_strvalue(&parser, parlist);   /* name or SYMBOL's val */

    parser_includefile(&parser, filename);

    free(parlist);
    parser_pop_fun();
}
