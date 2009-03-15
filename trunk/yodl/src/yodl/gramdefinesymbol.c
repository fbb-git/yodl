#include "yodl.h"

void gram_DEFINESYMBOL()
{
    register char *name;
    char *text;

    parser_push_fun("DEFINESYMBOL");

    name = parser_name_parlist(&parser, true);
    text = parser_parlist(&parser, COLLECT_SET);

    if (symbol_insert(parser.d_symtab_ptr, name, text) == FAILED)
        if (message_show(MSG_ERR))
            message("DEFINESYMBOL: `%s' multiply defined", name);

    if (message_show(MSG_NOTICE)) message("DEFINESYMBOL %s as `%s'\n", name,
                                                    string_short(text));
    parser_pop_fun();

    free(text);
    free(name);
}
