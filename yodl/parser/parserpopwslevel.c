#include "parser.ih"

void parser_pop_ws_level(register Parser *pp)
{
    register int value;

    if (!stack_size(&pp->d_ws_level_st))
        value = 0;
    else
    {
        value = stack_tos(&pp->d_ws_level_st)->u_int;
        stack_pop(&pp->d_ws_level_st);
    }
    p_set_ws_level(pp, pp->d_ws_level = value);
}
