#include "process.ih"

int p_parent(Process *pp, int *readPipe, int *writePipe)
{
    int status;
    size_t input_length;

    close(readPipe[WRITE]);                 /* Close unused pipe-ends       */
    close(writePipe[READ]);

    if ((input_length = strlen(pp->d_input)))
    {
        if
        (
            (size_t)write(writePipe[WRITE], pp->d_input, input_length)
            !=
            input_length
        )
        {
            char *input = new_str(string_short(pp->d_input));

            if (kill(pp->d_pid, SIGTERM))
                kill(pp->d_pid, SIGKILL);

            if (message_show(MSG_CRIT))
                message("%s: Can't pipe `%s' to `%s'",
                              pp->d_fname, input, string_short(pp->d_cmd));
            free(input);
        }
    }
    close(writePipe[WRITE]);

    p_fill_output(pp, readPipe[READ]);
    waitpid(pp->d_pid, &status, 0);
    return status;
}
