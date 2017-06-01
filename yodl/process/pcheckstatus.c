#include "process.ih"

bool p_check_status(Process *pp, int status)
{
    if (!WIFEXITED(status))
        if (message_show(MSG_ALERT))
            message("%s: `%s' terminated abnormally",
                                pp->d_fname, pp->d_short_cmd);
    if (!WEXITSTATUS(status))
        return true;

    if (message_show(MSG_WARNING))
        message("%s: `%s' terminated abnormally", pp->d_fname,
                                                    pp->d_short_cmd);
    return false;
}
