#include "yodl.h"

void gram_SYMBOLVALUE()
{
    register char *name;
    register HashItem *item;

    parser_push_fun("SYMBOLVALUE");

    name = parser_name_parlist(&parser,  false);
    item = hashmap_find(&symtab, name, SYMBOL);

    if (item == PFAILED && message_show(MSG_ERR))
        message("SYMBOLVALUE: symbol `%s' not defined", name);
    else
    {
        char const *value = symbol_value(item);

        if (message_show(MSG_NOTICE))
            message("SYMBOLVALUE: `%s' = %s", name, value);

        lexer_push_str(&parser.d_lexer, value);
    }

    parser_pop_fun();
    free(name);
}
