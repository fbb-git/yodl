
#include "yodl.h"

void gram_SYSTEM()
{
    char *cmd;

    parser_push_fun("SYSTEM");

    cmd = parser_parlist(&parser, COLLECT_SET);

    if (message_show(MSG_NOTICE))
        message("SYSTEM %s", string_short(cmd));

    Process process;
    process_construct(&process, "SYSTEM", cmd, NULL);

    process_system(&process);
    process_destruct(&process);

    parser_pop_fun();
}
