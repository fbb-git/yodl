#include "yodl.h"

void gram_DEFINECHARTABLE()
{
    register char *name;
    char *table;

    parser_push_fun("DEFINECHARTABLE");

    name = parser_name_parlist(&parser,  true);

    parser_push_ws_level(&parser, 0);       /* prevent ws consumption here  */
    table = parser_parlist(&parser, COLLECT_SET);
    parser_pop_ws_level(&parser);

    if (message_show(MSG_NOTICE)) message("DEFINECHARTABLE %s\n", name);

    if (!*table)                      /* may not be empty */
    {
        if (message_show(MSG_ERR))
            message("DEFINECHARTABLE: Character table `%s': missing table",
                    name);
    }
    else if
    (
        chartab_insert(&symtab, name, table) == FAILED
        &&
        message_show(MSG_ERR)
    )
            message("DEFINECHARTABLE: `%s' multiply defined", name);

    parser_pop_fun();
    free (name);
    free (table);
}
