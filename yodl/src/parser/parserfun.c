#include "parser.ih"

/* Should always succeed */

char const *parser_fun()
{
    return (char const *)stack_tos(&ps_fun_st);
}
