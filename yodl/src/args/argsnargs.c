#include "args.ih"

size_t args_nArgs()
{
    return args.d_argc - args.d_optind;
}
