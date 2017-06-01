#include "yodl.h"

void gram_FILENAME()
{
    parser_push_fun("FILENAME");
    parser_empty_parlist(&parser);

    if (message_show(MSG_NOTICE))
        message("FILENAME");

    (*parser.d_insert)(&parser, message_filename());

    parser_pop_fun();
}
