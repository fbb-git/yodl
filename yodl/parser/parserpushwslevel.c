#include "parser.ih"

void parser_push_ws_level(register Parser *pp, int value)
{
    register StackValue stValue;

    stValue.u_int = pp->d_ws_level;
    stack_push(&pp->d_ws_level_st, stValue);

    p_set_ws_level(pp, pp->d_ws_level = value);
}
