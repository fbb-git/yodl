#include "yodl.h"

void gram_USECOUNTER()
{
    register char *name;
    register HashItem *item;

    parser_push_fun("USECOUNTER");

    name = parser_name_parlist(&parser,  false);
    item = hashmap_find(&symtab, name, COUNTER);

    counter_add(item, 1);
    if (message_show(MSG_NOTICE))
        message("USECOUNTER: tos(%s)++", name);
    (*parser.d_insert)(&parser, counter_text(item));

    parser_pop_fun();
    free(name);
}
