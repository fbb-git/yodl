#include "yodl.h"

void gram_DEFINEMACRO()
{
    register char *name;
    size_t nargs;

    parser_push_fun("DEFINEMACRO");

    name  = parser_name_parlist(&parser,  true);

    if (parser_number_parlist(&parser, (int *)&nargs, true) == SUCCESS)
    {
        char *def   = parser_parlist(&parser, COLLECT_SET);

        if ((unsigned)nargs > 9 + 26 + 26)          /* 1-9, a-z, A-Z    */
        {
            if (message_show(MSG_ERR))
                message(
                    "DEFINEMACRO: max. %u arguments supported, not %d",
                    9 + 26 + 26, nargs);
        }
        else if
        (
            macro_insert(parser.d_symtab_ptr, name, def, nargs) == FAILED
        )
        {
            if (message_show(MSG_ERR))
                message("DEFINEMACRO: `%s' multiply defined", name);
        }
        else if (message_show(MSG_NOTICE))
            message("DEFINEMACRO: %s as `%s'", name, string_short(def));

        free(def);
    }

    parser_pop_fun();
    free(name);
}
