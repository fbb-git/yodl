#include "parser.ih"

char *p_end_nested(register Parser *pp, HANDLER_SET_ELEMENTS newSet)
{
    register char *text = 0;
                                            /* restore the handler set      */
    pp->d_handler = (bool (**)(struct Parser *))stack_tos(&pp->d_handler_st);
    stack_pop(&pp->d_handler_st);

    pp->d_insert =                          /* restore the inserter         */
        (void (*)(struct Parser *, char const *))stack_tos(&pp->d_insert_st);
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
