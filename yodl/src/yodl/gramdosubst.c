#include "yodl.h"

void gram_DOSUBST()
{
    register char *arg;
    int value;

    parser_push_fun("DOSUBST");
    parser_push_ws_level(&parser, 0);

    arg = parser_parlist(&parser, COLLECT_SET);

    if (
        arg != 0 && 
        sscanf(arg, "%u", &value) == 1 && 
        (value == 1 || value == 0)
    )
    {
        parser_allow_subst(&parser, value);
        if (message_show(MSG_NOTICE))
            message("DOSUBST(%s)", string_short(arg));
    }
    else if (message_show(MSG_ERR))
    {
        if (arg == 0)
            message("DOSUBST(...): missing argument");
        else
            message("DOSUBST: bad argument `%s' (0 or 1 expected)", arg);
    }

    parser_pop_ws_level(&parser);
    parser_pop_fun();

    free(arg);
}





