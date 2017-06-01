#include "yodl.h"

void gram_NEWCOUNTER()
{
    register char *name;

    parser_push_fun("NEWCOUNTER");
    name = parser_name_parlist(&parser,  false);

    warning("NEWCOUNTER is obsolete. DEFINECOUNTER should be used");

    if (counter_insert(&symtab, name, 0) == FAILED)
        if (message_show(MSG_ERR))
            message("NEWCOUNTER: `%s' multiply defined", name);

    if (message_show(MSG_NOTICE))
        message("NEWCOUNTER: %s", name);

    parser_pop_fun();
    free(name);
}
