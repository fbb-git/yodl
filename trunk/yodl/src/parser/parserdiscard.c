#include "parser.ih"

void parser_discard(register Parser *pp, SymbolType type,
                    char const *fun, char const *msg)
{
    register char *arg;

    parser_push_fun(fun);

    arg = parser_parlist(pp, COLLECT_SET);

    if (hashmap_erase(&symtab, arg, type) == SUCCESS)
    {
        if (message_show(MSG_NOTICE))
            message("%s: `%s' discarded", parser_fun(), arg);
    }
    else if (message_show(MSG_WARNING))
        message("%s: no %s`%s'", parser_fun(), msg, arg);

    parser_pop_fun();
    free(arg);
}
