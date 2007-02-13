
#include "yodl.h"

/*
    if numerical, arg is considered an ascii-character number
    otherwise, it must be a single printable character
*/
static char s_buf[2];

void gram_CHAR()
{
    register void (*saved)(struct Parser *, char const *);
    register char *arg;
    int  ascii;

    parser_push_fun("CHAR");

    parser_push_ws_level(&parser, 0);
    arg = parser_parlist(&parser, COLLECT_SET);

    if (message_show(MSG_NOTICE))
        message("CHAR(%s)", string_short(arg));

    if (isdigit(*arg) && sscanf(arg, "%u", (unsigned *)&ascii))
        s_buf[0] = ascii;
    else if (strlen(arg) == 1)
        s_buf[0] = *arg;
    else
        if (message_show(MSG_ERR))
            message("CHAR: non printable or no ascii value in `%s'", arg);

    saved = parser_suppress_chartab(&parser);

    (*parser.d_insert)(&parser, s_buf);
    parser.d_insert = saved;

    parser_pop_ws_level(&parser);

    parser_pop_fun();
    free(arg);
}
