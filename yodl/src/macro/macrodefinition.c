#include "macro.ih"

char const *macro_definition(Macro const *macro)
{
    return stack_tos(&macro->d_definition)->u_charCp;
}
