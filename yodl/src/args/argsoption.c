#include "args.ih"

bool args_option(int optchar)
{
    return strchr(string_str(&args.d_option), optchar) != NULL;
}
