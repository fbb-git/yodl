#include "args.ih"

bool args_options(char const *optchars)
{
    return string_find_first_of(&args.d_option, optchars) != FAILED;
}
