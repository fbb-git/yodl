#include "yodl.h"

void add_user_macros()
{
    char const *arg = args_multiarg('d');

    while (arg != PFAILED)
    {
        char *name;
        char *definition;
        char *eq_idx;

        if (!arg || !*arg)
            if (message_show(MSG_ERR))
                message("-d flag lacks macro name");

        name = new_str(arg);
        eq_idx =  strchr(name, '=');
        definition = "";

        if (eq_idx)
        {
            *eq_idx = 0;            /* note: a 0 may be written into optarg */
            definition = eq_idx + 1;
        }

        if (macro_insert(&symtab, name, definition, 0) == FAILED)
            if (message_show(MSG_ERR))
                message("`%s' (macro) multiply defined", name);

        free(name);
        arg = args_multiarg(0);
    }
}
