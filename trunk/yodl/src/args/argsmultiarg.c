#include "args.ih"

static char const *str;
static int option;

char const *args_multiarg(int optchar)
{
    register char const *pos;

    if (optchar)                                    /* new option:          */
    {
        str = string_str(&args.d_option);           /* use full string      */
        option = optchar;                           /* save the option char */
    }

    pos = strchr(str, option);

    if (pos)
    {
        size_t idx = pos - str;
        str = pos + 1;
        return args.d_optarg[idx];                  /* return optionstr.    */
    }

    return PFAILED;                                 /* or return PFAILED    */
}
