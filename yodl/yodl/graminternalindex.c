#include "yodl.h"

void gram_INTERNALINDEX()
{
    register char *msg;

    parser_push_fun("INTERNALINDEX");
    msg = parser_parlist(&parser, COLLECT_SET);

    if (parser.d_indexFile)
    {
        register char *cp;

        if (message_show(MSG_NOTICE))
            message("INTERNALINDEX %s", string_short(msg));
        msg = parser_nochartab_eval(&parser, msg);

        for (cp = msg; (cp = strchr(cp, '\n')); )       /* rm \n from entry */
            *cp = ' ';

        fprintf (parser.d_indexFile, "%ld %s\n",
                                ostream_offset(parser.d_outs_ptr), msg);
    }
    parser_pop_fun();
    free(msg);
}
