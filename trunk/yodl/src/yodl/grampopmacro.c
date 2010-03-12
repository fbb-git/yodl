#include "yodl.h"

void gram_POPMACRO()
{
    register char *name;
    register Macro *macro;

    parser_push_fun("POPMACRO");

    name = parser_name_parlist(&parser, false);
    macro = (Macro *)hashitem_value
            (
                hashmap_find(parser.d_symtab_ptr, name, MACRO)
            );

    if (macro != PFAILED && macro_pop(macro) == SUCCESS)
    {
        if (message_show(MSG_NOTICE))
            message("POPMACRO: %s", name);
    }
    else if (message_show(MSG_ERR))
        message("POPMACRO: Can't pop macro `%s'", name);

    parser_pop_fun();
    free(name);
}
