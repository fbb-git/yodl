#include "yodl.h"

void gram_INCWSLEVEL()
{
    parser_push_fun("INCWSLEVEL");
    parser_empty_parlist(&parser);
    parser_inc_ws_level(&parser);
    if (message_show(MSG_NOTICE))
        message("INCWSLEVEL: DEF level = %u", 
                                 (unsigned)parser_ws_level(&parser));
    parser_pop_fun();
}
