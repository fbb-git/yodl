#include "yodl.h"

void gram_PUSHCHARTABLE()
{
    char *arg;

    parser_push_fun("PUSHCHARTABLE");
    arg = parser_parlist(&parser, COLLECT_SET);

    if (chartab_use(parser.d_symtab_ptr, arg, true) == SUCCESS)
    {
        parser_apply_chartab(&parser);
        if (message_show(MSG_NOTICE))
            message("PUSHCHARTABLE: (%s)", arg);
    }
    else if (message_show(MSG_ERR))
        message("PUSHCHARTABLE: Can't push character table `%s'", arg);

    parser_pop_fun();
    free(arg);
}
