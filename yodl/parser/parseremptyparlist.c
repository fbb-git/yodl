#include "parser.ih"

void parser_empty_parlist(register Parser *pp)
{
    register char *arg = parser_parlist(pp, COLLECT_SET);

    if (*arg)
        if (message_show(MSG_WARNING))
            message("%s: Ignoring argument `%s'", parser_fun(),
                                            string_short(arg));
    free(arg);
}
