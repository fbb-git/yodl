#include "args.ih"

int args_optint(int optchar)
{
    register char const *arg = args_optarg(optchar);
    int value;

    if (!arg || sscanf (arg, "%d", &value) < 1)
    {
        message_show(MSG_ERR);
        message("No (int) argument with `-%c'", optchar);
        return FAILED;
    }

    return value;
}
