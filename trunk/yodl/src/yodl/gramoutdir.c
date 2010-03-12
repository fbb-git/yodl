#include "yodl.h"

void gram_OUTDIR()
{
    register char *dir;

    parser_push_fun("OUTDIR");
    parser_empty_parlist(&parser);

    dir = file_dirname(ostream_filename(parser.d_outs_ptr));

    if (message_show(MSG_NOTICE))
        message( "OUTDIR");
    (*parser.d_insert)(&parser, dir);

    parser_pop_fun();
    free(dir);
}
