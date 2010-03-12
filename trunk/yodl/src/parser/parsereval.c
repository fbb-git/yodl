#include "parser.ih"

char *parser_eval(register Parser *pp, register char *arg)
{
    if (!*arg)
        return arg;                         /* Nothing to evaluate  */

    p_begin_nested(pp, DEFAULT_SET);
    lexer_begin_nested(&pp->d_lexer, arg);
    free(arg);

    p_parse(pp);

    lexer_end_nested(&pp->d_lexer);
    arg = p_end_nested(pp, DEFAULT_SET);

    return arg;
}
