#include "yodl.h"

void gram_SETCOUNTER()
{
    register char *name;
    int value;

    parser_push_fun("SETCOUNTER");
    name = parser_name_parlist(&parser,  true);

    if (parser_number_parlist(&parser, &value, false) == SUCCESS)
    {
        register HashItem *item = hashmap_find(&symtab, name, COUNTER);

        counter_set(item, value);
        if (message_show(MSG_NOTICE))
            message("SETCOUNTER: tos(%s) = %d", name, value);
    }

    parser_pop_fun();
    free(name);
}
