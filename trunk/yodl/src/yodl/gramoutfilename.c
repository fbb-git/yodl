#include "yodl.h"

void gram_OUTFILENAME()
{
    parser_push_fun("OUTFILENAME");
    parser_empty_parlist(&parser);
    if (message_show(MSG_NOTICE))
        message("OUTFILENAME");

    (*parser.d_insert)(&parser, ostream_filename(parser.d_outs_ptr));
    parser_pop_fun();
}
