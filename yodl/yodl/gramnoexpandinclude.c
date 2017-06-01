#include "yodl.h"

/*
    No attempt is made to find the file in XXincludepath.
    Use NOEXPANDPATHINCLUDE for that
*/

void gram_NOEXPANDINCLUDE()
{
    char *parlist;
    char const *filename;

    parser_push_fun("NOEXPANDINCLUDE");

    parlist = parser_parlist(&parser, COLLECT_SET);

    if (message_show(MSG_NOTICE))
        message("NOEXPANDINCLUDE `%s'", parlist);

    filename = parser_strvalue(&parser, parlist);   /* name or SYMBOL's val */

    parser_noexpand_include(&parser, filename, false);

    free(parlist);
    parser_pop_fun();
}
