#include "yodl.h"

bool check_live_data(register char const *cmd)
{
    bool report = false;
    char const *livedata = args_optarg('l');

    if (!livedata)
    {
        message_show(MSG_ERR);
        message("%s [livedata = none]: won't execute `%s'",
                            parser_fun(), string_short(cmd));
        return false;
    }

    if (!strcmp(livedata, "0") || !strcmp(livedata, "none"))
    {
        message_show(MSG_ERR);
        message("%s [livedata = %s]: won't execute `%s'",
                            parser_fun(), livedata, string_short(cmd));
        return false;
    }

    if (!strcmp(livedata, "1") || !strcmp(livedata, "confirm"))
    {
        if (!userconfirm(cmd))
            return false;

        report = true;
    }

    if (report || !strcmp(livedata, "2") || !strcmp(livedata, "report"))
    {
        if (message_show(MSG_WARNING))
            message("%s [livedata = %s]: executing `%s'",
                               parser_fun(), livedata, string_short(cmd));
        report = true;
    }

    if (report || !strcmp(livedata, "3") || !strcmp(livedata, "ok"))
        return true;

    message_show(MSG_ERR);
    message("Invalid argument for `-l': `%s' ", livedata);
    return false;
}

