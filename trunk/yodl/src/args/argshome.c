#include "args.ih"

char const *args_home()
{
    return args.d_home ? args.d_home : NULL;
}
