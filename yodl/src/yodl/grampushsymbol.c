#include "yodl.h"

void gram_PUSHSYMBOL()
{
    register char *name;
    char *arg;
    register HashItem *item;

    parser_push_fun("PUSHSYMBOL");

    name = parser_name_parlist(&parser,  true);
    arg  = parser_parlist(&parser, COLLECT_SET);
    item = hashmap_find(parser.d_symtab_ptr, name, SYMBOL);

    if
    (
        (
            item != PFAILED
            &&
            stack_push((Stack *)hashitem_value(item), arg) == SUCCESS
        )
        ||
        symbol_insert(parser.d_symtab_ptr, name, arg) != FAILED
    )
    {
        if (message_show(MSG_NOTICE))
            message("PUSHSYMBOL %s (= %s)", name, string_short(arg));
    }
    else if (message_show(MSG_ERR))
        message("PUSHSYMBOL: `%s' multiply defined", name);

    parser_pop_fun();
    free (name);
}
