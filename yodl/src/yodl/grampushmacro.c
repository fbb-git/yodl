#include "yodl.h"

void gram_PUSHMACRO()
{
    register char *name;
    int args;

    parser_push_fun("PUSHMACRO");

    name  = parser_name_parlist(&parser, true);
    if (parser_number_parlist(&parser, &args, true) == SUCCESS)
    {
        char *def   = parser_parlist(&parser, COLLECT_SET);
        size_t nargs = args;

        if (nargs > 9 + 26 + 26)                /* 1-9, a-z, A-Z    */
        {
            if (message_show(MSG_ERR))
                message("PUSHMACRO: max. %d arguments supported, not %d",
                        9 + 26 + 26, args);
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
