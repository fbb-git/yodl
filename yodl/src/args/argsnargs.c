#include "args.ih"

unsigned args_nArgs()
{
    return args.d_argc - args.d_optind;
}
