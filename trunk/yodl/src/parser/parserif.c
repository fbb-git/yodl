#include "parser.ih"

void parser_if(register Parser *pp, SymbolType type, char const *fun)
{
    char *name;
    register HashItem *item;
    char *truelist;
    char *falselist;

    parser_push_fun(fun);

    name      = parser_name_parlist(pp, true);
    item      = hashmap_find(pp->d_symtab_ptr, name, type);
    truelist  = parser_parlist(pp, COLLECT_SET);
    parser_skipws(pp);

    falselist       = parser_parlist(pp, COLLECT_SET);

    if (message_show(MSG_NOTICE))
        message("%s `%s' %s", parser_fun(), string_short(name),
                                item == PFAILED  ? "(not found)": "(found)");

    lexer_push_str(&pp->d_lexer, item == PFAILED ? falselist : truelist);

    parser_pop_fun();

    free (name);                          /* return used memory */
    free (truelist);
    free (falselist);
}
