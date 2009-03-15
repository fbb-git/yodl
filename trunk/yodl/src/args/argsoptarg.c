#include "args.ih"

char const *args_optarg(int optchar)
{
    register char const *opt = string_str(&args.d_option);
    register char const *pos = strchr(opt, optchar);

    return pos ? args.d_optarg[pos - opt] : 0;
}
