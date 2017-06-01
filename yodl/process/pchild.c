#include "process.ih"

/*
    This function specifies readPipe and writePipe, but in the prototype
    the names are reversed: there writePipe and readPipe are used.
    The prototype is given from the point of view of the parent code,
    which first specifies the writePipe.
    Here, we're in the child-process itself, and the parent's writePipe
    becomes the child's readPipe.
*/
int p_child(Process *pp, int *readPipe, int *writePipe)
{
    char **argv = p_split(pp);              /* construct argv               */

    close(readPipe[WRITE]);                 /* Close unused pipe-ends       */
    close(writePipe[READ]);

    if                                      /* Use our descriptors for      */
    (                                       /* standard streams             */
        dup2(readPipe[READ], STDIN_FILENO) < 0
        ||
        dup2(writePipe[WRITE], STDOUT_FILENO) < 0
    )
        if (message_show(MSG_ALERT))
            message("%s: Can't redirect STDIN and/or STDOUT");

    close(readPipe[READ]);                  /* close superfluous original  */
    close(writePipe[WRITE]);                /* parts                        */

    return execvp(*argv, argv);             /* exec the program             */
                                            /* (program exits or -1 is      */
                                            /* returned when exec fails     */
}
