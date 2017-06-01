#include "yodl.h"

void gram_POPCHARTABLE()
{
    parser_push_fun("POPCHARTABLE");

    parser_empty_parlist(&parser);

    if (message_show(MSG_NOTICE))
        message("POPCHARTABLE()");

    if (chartab_pop() == SUCCESS)
        parser_apply_chartab(&parser);
    else if (message_show(MSG_ERR))
            message("POPCHARTABLE: Character table stack underflow");

    parser_pop_fun();
}
