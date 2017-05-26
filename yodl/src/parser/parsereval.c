#include "parser.ih"

char *parser_eval(register Parser *pp, register char *arg)
{
    return parser_evalSet(pp, arg, DEFAULT_SET);
}

char *parser_evalSet(register Parser *pp, register char *arg,
                 HANDLER_SET_ELEMENTS set)
{
    if (!*arg)
        return arg;                         /* Nothing to evaluate  */

    p_begin_nested(pp, set);
    lexer_begin_nested(&pp->d_lexer, arg);

    free(arg);

    p_parse(pp);

    lexer_end_nested(&pp->d_lexer);
    arg = p_end_nested(pp, set);

    return arg;
}
