#include "macro.ih"

unsigned macro_nArgs(Macro const *macro)
{
    return (unsigned)stack_tos(&macro->d_arg);
}
