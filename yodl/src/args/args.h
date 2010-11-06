#ifndef INCLUDED_ARGS_H_
#define INCLUDED_ARGS_H_

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

extern int args_data;

char const *args_arg(size_t idx);               /* 0: 1st arg not counting  */
                                                /*    argv[0]               */
void        args_construct(int argc, char **argv, char *options,
                           LongOption const *long_options);

                                                /* get the next occurrence  */
                                                /* of a series of optargs   */
                                                /* to get the next one,     */
                                                /* give optarg 0            */
                                                /* return value 0: no arg   */
                                                /* PFAILED: no (more)       */
char const *args_multiarg(int optchar);         /* optchars specified       */
char const *args_optarg(int optchar);           /* 0: no such option        */
                                                /* or value of option       */
int         args_optint(int optchar);           /* int value of option      */
                                                /* optchar or FAILED and    */
                                                /* error message            */

/* 
    Internal Arg use only. Not used outside of this directory functions, needed here
    to allow proper compilation of the static inline functions below
*/

#include "../string/string.h"

typedef struct
{
    String d_option;            /* all option characters encountered        */
    char  **d_optarg;           /* all option arguments, or 0-pointers      */
                                /* the location of the option values        */
                                /* matches the index of the corresponding   */
                                /* character in d_option                    */
    char  **d_argv;
    int     d_argc;

    char   *d_home;
    char   *d_programName;

    char   *d_initial_dir;
    bool    d_ok;
    int     d_optind;
}
Args;

extern Args args;


/*  public interface continues from here */


static inline char const *args_home()
{
    return args.d_home ? args.d_home : NULL;
}

static inline char const *args_initial_dir()
{
    return args.d_initial_dir;
}

static inline size_t args_nArgs()
{
    return args.d_argc - args.d_optind;
}

static inline bool args_ok()
{
    return args.d_ok;
}

static inline bool args_option(int optchar)
{
    return strchr(string_str(&args.d_option), optchar) != NULL;
}

static inline bool args_options(char const *optchars)
{
    return string_find_first_of(&args.d_option, optchars) != UFAILED;
}

static inline char const *args_programName()
{
    return args.d_programName;
}

#endif
