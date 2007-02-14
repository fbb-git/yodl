#include "yodl.h"

void gram_PUSHMACRO()
{
    register char *name;
    size_t nargs;

    parser_push_fun("PUSHMACRO");

    name  = parser_name_parlist(&parser, true);
    if (parser_number_parlist(&parser, (int *)&nargs, true) == SUCCESS)
    {
        char *def   = parser_parlist(&parser, COLLECT_SET);

        /* should be parser function:   */

        if ((size_t)nargs > 9 + 26 + 26)          /* 1-9, a-z, A-Z    */
        {
            if (message_show(MSG_ERR))
                message("PUSHMACRO: max. %u arguments supported, not %d",
                        9 + 26 + 26, nargs);
        }
        else
        {
            Macro *macro = (Macro *)
                        hashitem_value
                        (
                            hashmap_find(parser.d_symtab_ptr, name, MACRO)
                        );
            if
            (
                (
                    macro != PFAILED
                    &&
                    macro_push(macro, def, nargs) == SUCCESS
                )
                ||
                macro_insert(parser.d_symtab_ptr, name, def, nargs) == SUCCESS
            )
            {
                if (message_show(MSG_NOTICE))
                    message("PUSHMACRO: %s as `%s'", name, string_short(def));
            }
            else
                if (message_show(MSG_ERR))
                    message("PUSHMACRO: `%s' multiply defined", name);
        }
        free (def);
    }

    parser_pop_fun();

    free (name);
}
