#include "parser.ih"

/*
    The weird casts are to get rid of the const to obtain a plain void *
    However, I think I'll change the type of the stack elements so that it 
    can store void *, void const *, and the parser's functions
*/
void parser_push_fun(char const *fun)
{
    stack_push(&ps_fun_st, *(char **)(void *)&fun);  /* fun not modified */
}
