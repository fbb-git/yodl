#include "yodl.h"

void add_user_symbols()
{
    char const *arg = args_multiarg('D');

    while (arg != PFAILED)
    {
        char *symbol;
        char *value;
        char *eq_idx;

        if (!arg || !*arg)
            if (message_show(MSG_ERR))
                message("-D flag lacks symbol name");

        symbol = new_str(arg);
        eq_idx =  strchr(symbol, '=');
        value = "";

        if (eq_idx)
        {
            *eq_idx = 0;            /* note: a 0 may be written into optarg */
            value = eq_idx + 1;
        }

        if (symbol_insert(&symtab, symbol, value) == FAILED)
            if (message_show(MSG_ERR))
                message("`%s' (symbol) multiply defined", symbol);

        free(symbol);
        arg = args_multiarg(0);
    }
}
