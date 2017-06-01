#include "yodl.h"

void gram_PUSHWSLEVEL()
{
    char *arg;
    int value;
    Result res = SUCCESS;

    parser_push_fun("PUSHWSLEVEL");

    arg  = parser_parlist(&parser, COLLECT_SET);

    if (!*arg)
        value = 0;
    else
        res = parser_value(&parser, &value, arg);

    if (res == SUCCESS)
        parser_push_ws_level(&parser, value);
    else if (message_show(MSG_ERR))
        message("PUSHWSLEVEL: argument (`%s') must be empty, value or "
                                                            "counter", arg);
    parser_pop_fun();
    free(arg);
}
