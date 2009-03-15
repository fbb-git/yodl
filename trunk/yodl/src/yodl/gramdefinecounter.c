#include "yodl.h"

void gram_DEFINECOUNTER()
{
    register char *name;
    int  value;

    parser_push_fun("DEFINECOUNTER");

    name = parser_name_parlist(&parser,  true);
    if (parser_number_parlist(&parser,  &value, false) == SUCCESS)
    {
        if
        (
            counter_insert(&symtab, name, value) == FAILED
            &&
            message_show(MSG_ERR)
        )
            message("DEFINECOUNTER: `%s' multiply defined", name);
        else if (message_show(MSG_NOTICE))
            message("DEFINECOUNTER: %s (= %d)", name, value);
    }

    parser_pop_fun();
    free (name);
}
