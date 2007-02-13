#include "parser.ih"

void parser_push_fun(char const *fun)
{
    register StackValue stValue;

    stValue.u_charCp = fun;
    stack_push(&ps_fun_st, stValue);
}
