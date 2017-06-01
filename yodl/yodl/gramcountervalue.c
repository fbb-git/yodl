#include "yodl.h"

void gram_COUNTERVALUE()
{
    register char *name;
    register HashItem *item;
    char const *value;

    parser_push_fun("COUNTERVALUE");

    name = parser_name_parlist(&parser,  false);
    item = hashmap_find(&symtab, name, COUNTER);

    if (item == PFAILED && message_show(MSG_ERR))
        message("COUNTERVALUE: counter `%s' not defined", name);
    else
    {
        value = counter_text(item);
        if (message_show(MSG_NOTICE))
            message("COUNTERVALUE: `%s' = %s", name, value);

        (*parser.d_insert)(&parser, value);
    }

    parser_pop_fun();
    free(name);
}
