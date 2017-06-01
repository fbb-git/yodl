#include "yodl.h"

void gram_POPWSLEVEL()
{
    parser_push_fun("POPWSLEVEL");
    parser_empty_parlist(&parser);
    parser_pop_ws_level(&parser);
    parser_pop_fun();
}
