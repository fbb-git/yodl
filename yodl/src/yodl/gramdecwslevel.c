#include "yodl.h"

void gram_DECWSLEVEL()
{
    parser_push_fun("DECWSLEVEL");
    parser_empty_parlist(&parser);
    parser_dec_ws_level(&parser);
    if (message_show(MSG_NOTICE))
        message("DECWSLEVEL DEF level = %u\n", 
                                (unsigned)parser_ws_level(&parser));
    parser_pop_fun();
}
