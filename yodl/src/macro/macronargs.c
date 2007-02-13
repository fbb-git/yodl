#include "macro.ih"

unsigned macro_nArgs(Macro const *macro)
{
    return stack_tos(&macro->d_arg)->u_unsigned;
}
