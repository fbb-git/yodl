#include "yodl.h"

void gram_ADDTOSYMBOL()
{
    register char *name;
    char *text;

    parser_push_fun("ADDTOSYMBOL");

    name = parser_name_parlist(&parser,  true);
    text = parser_parlist(&parser, COLLECT_SET);

    symbol_add(hashmap_find(&symtab, name, SYMBOL), text);
    if (message_show(MSG_NOTICE))
        message("ADDTOSYMBOL tos(%s) += \"%s\"",  name, string_short(text));
    parser_pop_fun();
    free(text);
    free(name);
}
