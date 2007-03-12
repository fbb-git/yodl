#include "yodl.h"

void gram_FPUTS()
{
    char *msg;
    register char *name;
    register char *name_short;
    FILE *file;

    parser_push_fun("FPUTS");

    msg = parser_parlist(&parser, COLLECT_SET);
    parser_skipws(&parser);
    name = parser_parlist(&parser, COLLECT_SET);
    name_short = new_str(string_short(name));
    if (message_show(MSG_NOTICE))
        message("FPUTS %s: %s", name_short, string_short (msg));

    file = file_open(name, "a");
    fputs(msg = parser_eval(&parser, msg), file);
    fclose (file);

    parser_pop_fun();

    free (name_short);
    free (name);
    free (msg);
}
