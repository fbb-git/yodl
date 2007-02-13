#include "parser.ih"

void parser_skipws(register Parser *pp)
{
    register StackValue stValue;
                                        /* set up handler set to use        */
    stValue.u_Pfun1p = pp->d_handler;
    stack_push(&pp->d_handler_st, stValue);
    pp->d_handler = ps_handlerSet[SKIPWS_SET];

    p_parse(pp);
                                            /* restore the handler set      */
    pp->d_handler = stack_tos(&pp->d_handler_st)->u_Pfun1p;
    stack_pop(&pp->d_handler_st);
}
