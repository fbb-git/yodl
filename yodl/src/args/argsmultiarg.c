#include "args.ih"

static char const *str;
static char const *searchStr;
static int option;

// The full string is a string containing all the single-letter options that
// were specified. E.g., DDvD if -D -D -v -D was specified. When called with a
// non-0 argument str and searchStr are (re)initialized to the beginning of
// the string. Then, and at each subsequent call using a zero-arg the saved
// opchar is searched from where searchStr points. Following this search
// searchStr is incremented, unless it points to the option string's 0-byte
// The location of the optchar in str is then used as index in the array of
// args.d_optarg, returning the associated value.

char const *args_multiarg(int optchar)
{
    if (optchar)                                    /* new option:          */
    {
        str = string_str(&args.d_option);           /* use full string      */
        searchStr = str;
        option = optchar;                           /* save the option char */
    }

    register char const *pos = strchr(searchStr, option);
    if (*searchStr != 0)                            // shift to the next ch.*/
        ++searchStr;

    if (pos)
    {
        size_t idx = pos - str;
        return args.d_optarg[idx];                  /* return optionstr.    */
    }

    return PFAILED;                                 /* or return PFAILED    */
}
