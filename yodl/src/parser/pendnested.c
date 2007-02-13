#include "parser.ih"

char *p_end_nested(register Parser *pp, HANDLER_SET_ELEMENTS newSet)
{
    register char *text = 0;
                                            /* restore the handler set      */
    pp->d_handler = stack_tos(&pp->d_handler_st)->u_Pfun1p;
    stack_pop(&pp->d_handler_st);
                                            /* restore the inserter         */
    pp->d_insert = stack_tos(&pp->d_insert_st)->u_Pfun2p;
    stack_pop(&pp->d_insert_st);

    switch (newSet)
    {
        case COLLECT_SET:
        case DEFAULT_SET:
                                            /* obtain the nested text       */
            text = string_release(pp->d_string_ptr);
            pp->d_string_ptr = stack_tos(&pp->d_string_st)->u_Stringp;
            stack_pop(&pp->d_string_st);
        break;

        case NOTRANS_SET:
        case NOEXPAND_SET:
            parser_pop_ws_level(pp);
        break;

        default:
        break;
    }
    return text;
}
