
#include "yodl.h"

void gram_SYSTEM()
{
    char *cmd;

    parser_push_fun("SYSTEM");

    cmd = parser_parlist(&parser, COLLECT_SET);

    if (message_show(MSG_NOTICE))
        message("SYSTEM %s", string_short(cmd));

    if (!check_live_data(cmd))
        free(cmd);
    else
    {
        Process process;
        process_construct(&process, "SYSTEM", cmd, NULL);

        process_system(&process);
        process_destroy(&process);
    }

    parser_pop_fun();
}
