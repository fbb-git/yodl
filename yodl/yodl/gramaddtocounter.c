#include "yodl.h"

void gram_ADDTOCOUNTER()
{
    register char *name;
    int value;

    parser_push_fun("ADDTOCOUNTER");

    name = parser_name_parlist(&parser, true);

    if (parser_number_parlist(&parser, &value, false) == SUCCESS)
    {
        counter_add(hashmap_find(&symtab, name, COUNTER), value);
        if (message_show(MSG_NOTICE))
            message("ADDTOCOUNTER: tos(%s) += %d", name, value);
    }

    parser_pop_fun();
    free(name);
}
