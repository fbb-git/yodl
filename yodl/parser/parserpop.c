#include "parser.ih"

void parser_pop(register Parser *pp, SymbolType type,
                                        char const *fun, char const *msg)
{
    char *name;
    register HashItem *item;

    parser_push_fun(fun);

    name = parser_name_parlist(pp, false);
    item = hashmap_find(parser.d_symtab_ptr, name, type);

    if (hashitem_pop(item) == FAILED)
        if (message_show(MSG_ERR))
            message("%s: Can't pop %s `%s'", fun, msg, name);

    parser_pop_fun();
    free(name);
}
