#include "macro.ih"

size_t macro_nArgs(Macro const *macro)
{
    return stack_tos(&macro->d_arg)->u_size_t;
}
