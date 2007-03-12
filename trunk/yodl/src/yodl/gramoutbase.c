#include "yodl.h"

void gram_OUTBASE()
{
    register char *base;

    parser_push_fun("OUTBASE");
    base = file_basename(ostream_filename(parser.d_outs_ptr));

    parser_empty_parlist(&parser);
    if (message_show(MSG_NOTICE))
        message("OUTBASE");

    (*parser.d_insert)(&parser, base);

    parser_pop_fun();
    free(base);
}
