#include "yodl.h"

void gram_USECHARTABLE()
{
    char *arg;

    parser_push_fun("USECHARTABLE");

    arg = parser_parlist(&parser, COLLECT_SET);

    if (chartab_use(parser.d_symtab_ptr, arg, false) == SUCCESS)
    {
        parser_apply_chartab(&parser);
        if (message_show(MSG_NOTICE))
            message("USECHARTABLE: %s", arg);
    }
    else if (message_show(MSG_ERR))
        message("USECHARTABLE: Chartable `%s' not defined", arg);

    parser_pop_fun();
    free(arg);
}
