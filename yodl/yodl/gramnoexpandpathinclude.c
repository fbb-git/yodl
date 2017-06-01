#include "yodl.h"

void gram_NOEXPANDPATHINCLUDE()
{
    register char *parlist;

    parser_push_fun("NOEXPANDPATHINCLUDE");

    parlist = parser_parlist(&parser, COLLECT_SET);
    parser_noexpand_include(&parser, parlist , true);
    free(parlist);

    parser_pop_fun();
}
