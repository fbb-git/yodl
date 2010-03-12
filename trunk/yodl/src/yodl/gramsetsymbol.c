#include "yodl.h"

void gram_SETSYMBOL()
{
    register char *name;
    char *text;
    register HashItem *item;

    parser_push_fun("SETSYMBOL");

    name = parser_name_parlist(&parser,  true);
    text = parser_parlist(&parser, COLLECT_SET);
    item = hashmap_find(&symtab, name, SYMBOL);

    symbol_set(item, text);
    if (message_show(MSG_NOTICE))
        message("SETSYMBOL tos(%s) = \"%s\"", name, string_short(text));
    parser_pop_fun();
    free(text);
    free(name);
}
