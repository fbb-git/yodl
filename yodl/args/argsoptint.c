#include "args.ih"

int args_optint(int optchar)
{
    register char const *arg = args_optarg(optchar);
    int value;

    if (!arg || sscanf (arg, "%d", &value) < 1)
    {
        message_show(MSG_ERR);
        message("No (int) argument with `-%c'", (char)optchar);
        return FAILED;
    }

    return value;
}
