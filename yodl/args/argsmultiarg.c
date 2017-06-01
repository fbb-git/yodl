#include "args.ih"

static char *str;
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
    if (optchar)                                    // new option:          
    {
        if (!str)
            str = (char *)string_str(&args.d_option); // use full string

        option = optchar;                           // save the option char
    }

    register char *pos = strchr(str, option);

    if (pos)
    {
        size_t idx = pos - str;
        *pos = ' ';                                 // this option has now 
                                                    // been processed.

        return args.d_optarg[idx];                  // return optionstr.
    }

    return PFAILED;                                 // or return PFAILED
                                                    // in which case there was
                                                    // no option argument
}
