#include "parser.ih"

/* Should always succeed */

char const *parser_fun()
{
    return stack_tos(&ps_fun_st)->u_charCp;
}
