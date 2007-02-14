#include "process.ih"

char **p_split(Process *pp)
{
    size_t idx = 0;
    char **argv = new_memory(1, sizeof(char *));    /* one extra -> NULL    */
    char *cp =                                      /* get the first arg    */
          strtok(pp->d_cmd, " \t\n");

    while (cp)
    {
        argv[idx++] = cp;
        new_size(&argv, idx + 1, idx, sizeof(char *));
        cp = strtok(NULL, " \t\n");
    }

    if (!idx)
        if (message_show(MSG_CRIT))
            message("%s: Missing program name", pp->d_fname);

    argv[idx] = NULL;
    return argv;
}
