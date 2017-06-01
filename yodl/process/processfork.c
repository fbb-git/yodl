#include "process.ih"

void process_fork(Process *pp)
{
                /* NB: ALERT messages terminate the current process     */
    int readPipe[2];                    /* Yodl reads from this pipe    */
    int writePipe[2];                   /* Yodl writes to this pipe     */

    if (pipe(readPipe) != 0 || pipe(writePipe) != 0)
        if (message_show(MSG_ALERT))
            message("%s: Can't construct pipes", pp->d_fname);

    pp->d_pid = fork();                 /* Do the fork                  */

    if (pp->d_pid == -1)                /* fork fails                   */
        if (message_show(MSG_ALERT))
            message("%s: Can't fork(%s)", pp->d_fname, pp->d_short_cmd);

    if (!pp->d_pid)                     /* No pid: so child process     */
        exit(p_child(pp, writePipe, readPipe));

                                        /* Got pid: so parent process   */
    p_check_status(pp, p_parent(pp, readPipe, writePipe));
}
