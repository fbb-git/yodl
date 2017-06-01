#include "yodl.h"

void gram_COMMENT()
{
    parser_push_fun("COMMENT");

    if (message_show(MSG_NOTICE))
        message("COMMENT(...)");
    parser_parlist(&parser, IGNORE_SET);

    parser_pop_fun();
}
