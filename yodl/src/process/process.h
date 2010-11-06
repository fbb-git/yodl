#ifndef INCLUDED_PROCESS_H_
#define INCLUDED_PROCESS_H_

#include "../string/string.h"

typedef struct
{
    int d_pid;
    char const *d_fname;
    char *d_cmd;
    char *d_short_cmd;
    char *d_input;
    String *d_output;
}
Process;
                                /* cmd and input are freed by _destroy()    */
                                /* input may be NULL (or point to an empty  */
                                /* String if there's nothing to pipe        */
                                /* input is not used with _system()         */
void    process_construct(Process *pp, char const *fname,
                          char *cmd, char *input);
void    process_destroy(Process *pp);
void    process_fork(Process *pp);                  /* calls execvp()       */
void    process_system(Process *pp);                /* calls /bin/sh -c cmd */

static inline String const *process_output(Process *pp)
{
    return pp->d_output;
}

#endif
