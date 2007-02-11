#ifndef _INCLUDED_ARGS_H_
#define _INCLUDED_ARGS_H_

#include <getopt.h>
#include "../root/root.h"

/*
    Provide args_construct with the optionstring for getopt() and a pointer to
long-options structs, terminating in a final element of 0's.

*/

typedef struct
{
    char const     *d_name;
    int             d_type;
    unsigned char   d_value;
}
LongOption;


char const *args_arg(unsigned idx);             /* 0: 1st arg not counting  */
                                                /*    argv[0]               */
char const *args_programName(void);
void        args_construct(int argc, char **argv, char *options,
                           LongOption const *long_options);
char const *args_home(void);
char const *args_initial_dir(void);
                                                /* get the next occurrence  */
                                                /* of a series of optargs   */
                                                /* to get the next one,     */
                                                /* give optarg 0            */
                                                /* return value 0: no arg   */
                                                /* PFAILED: no (more)       */
char const *args_multiarg(int optchar);         /* optchars specified       */
unsigned    args_nArgs(void);
bool        args_ok(void);
bool        args_options(char const *optchars); /* any option set ?         */
bool        args_option(int optchar);           /* option ?                 */
char const *args_optarg(int optchar);           /* 0: no such option        */
                                                /* or value of option       */
int         args_optint(int optchar);           /* int value of option      */
                                                /* optchar or FAILED and    */
                                                /* error message            */
#endif
