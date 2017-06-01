#include "process.ih"

void process_system(Process *pp)
{
                /* NB: ALERT messages terminate the current process     */
    int status = system(pp->d_cmd);

                                        /* fork fails                   */
    if (status == -1 && message_show(MSG_ALERT))
        message("%s: Can't execute system(%s)", pp->d_fname, pp->d_short_cmd);

    p_check_status(pp, status);
}
