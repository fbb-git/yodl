#include "parser.ih"

void parser_skipws(register Parser *pp)
{
                                        /* set up handler set to use        */
    stack_push(&pp->d_handler_st, pp->d_handler);
    pp->d_handler = ps_handlerSet[SKIPWS_SET];

    p_parse(pp);
                                            /* restore the handler set      */
    pp->d_handler = (bool (**)(struct Parser *))stack_tos(&pp->d_handler_st);
    stack_pop(&pp->d_handler_st);
}
