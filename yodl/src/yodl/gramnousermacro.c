#include "yodl.h"

void gram_NOUSERMACRO()
{
    register char *arg;
    register char *cp;

    parser_push_fun("DEFINEMACRO");

    arg = parser_parlist(&parser, COLLECT_SET);
    if (message_show(MSG_NOTICE))
        message("NOUSERMACRO(%s)", string_short(arg));

    cp = strtok(arg, " :,;\t\n");
    while (cp)
    {
        if (message_show(MSG_NOTICE))
            message("NOUSERMACRO: add %s", cp);

        if
        (
            hashmap_insert
            (
                parser.d_symtab_ptr,
                hashitem_construct(NOUSERMACRO, cp, 0, root_nop)
            ) == FAILED
        )
            if (message_show(MSG_ERR))
                message("NOUSERMACRO: `%s' multiply defined", cp);

        cp = strtok (NULL, " :,;\t\n");
    }

    parser_pop_fun();
    free(arg);
}
