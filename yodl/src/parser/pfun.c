#include "parser.ih"

char const *p_fun()
{
    return stack_tos(&ps_fun_st);
}
