#include "parser.ih"

void parser_pop_fun()
{
    stack_pop(&ps_fun_st);
}
