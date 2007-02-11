#include "parser.ih"

char *p_end_nested(register Parser *pp, HANDLER_SET_ELEMENTS newSet)
{
    Parser_Ufunvoid saved;
    register char *text = 0;
                                            /* restore the handler set      */
    pp->d_handler = (bool (**)(struct Parser *))stack_tos(&pp->d_handler_st);
    stack_pop(&pp->d_handler_st);

    saved.u_voidp = stack_tos(&pp->d_insert_st);
    pp->d_insert = saved.u_funp;           /* restore the inserter         */
    stack_pop(&pp->d_insert_st);

    switch (newSet)
    {
        case COLLECT_SET:
        case DEFAULT_SET:
                                            /* obtain the nested text       */
            text = string_release(pp->d_string_ptr);
            pp->d_string_ptr = (String *)stack_tos(&pp->d_string_st);
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
