#include "args.ih"

char const *args_arg(unsigned idx)
{
    if (idx >= args_nArgs() && message_show(MSG_ERR))
        message("%u: argument bounds exceeded (n = %u)", idx, args_nArgs());

    return args.d_argv[idx + args.d_optind];
}
