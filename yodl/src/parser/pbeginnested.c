#include "parser.ih"

void p_begin_nested(register Parser *pp, HANDLER_SET_ELEMENTS newSet)
{
    register StackValue stValue;
    register StackValue saved;

                                        /* set up handler set to use        */
    stValue.u_Pfun1p = pp->d_handler;
    stack_push(&pp->d_handler_st, stValue);
    pp->d_handler = ps_handlerSet[newSet];

                                        /* save the  inserter               */
    saved.u_Pfun2p = pp->d_insert;
    stack_push(&pp->d_insert_st, saved);

    switch (newSet)
    {
        case COLLECT_SET:
            stValue.u_Stringp = pp->d_string_ptr;
            stack_push(&pp->d_string_st, stValue);
            pp->d_string_ptr = string_new(0);

            pp->d_insert = p_insert_no_chartab_string;
        break;

        case DEFAULT_SET:
            stValue.u_Stringp = pp->d_string_ptr;
            stack_push(&pp->d_string_st, stValue);

            pp->d_string_ptr = string_new(0);

            pp->d_insert =
                    pp->d_insert = chartab_isActive() ?
                        p_insert_chartab_string
                    :
                        p_insert_no_chartab_string;
        break;

        case IGNORE_SET:
            pp->d_insert = p_insert_nothing;
        break;

        case NOTRANS_SET:
            parser_suppress_chartab(pp);
        /* FALL THROUGH */

        case NOEXPAND_SET:
            parser_push_ws_level(pp, 0);
        break;

        default:
        break;
    }
}
