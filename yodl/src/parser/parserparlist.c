#include "parser.ih"

/*
    parser_parlist is called to retrieve a parameter list. The parameter list
    is inserted/interpreted thereafter. Therefore, no CHARTAB handling should
    be done by the parsing.
*/

char *parser_parlist(register Parser *pp, HANDLER_SET_ELEMENTS newSet)
{
    register char *str = 0;
    register StackValue stValue;

    if (lexer_lex(&pp->d_lexer) != TOKEN_OPENPAR)
        if (message_show(MSG_CRIT))
            message("%s: Missing parameter list. `(' expected", parser_fun());

    pp->d_parlist_lineno = message_lineno();
    free(pp->d_parlist_filename);                   /* remember the file    */
                                                    /* where the parlist    */
                                                    /* starts               */
    pp->d_parlist_filename = new_str(message_filename());

    lexer_unget_matched(&pp->d_lexer);

    stValue.u_size_t = pp->d_paren;
    stack_push(&pp->d_paren_st, stValue);
    pp->d_paren = 0;

    p_begin_nested(pp, newSet);
    p_parse(pp);
    str = p_end_nested(pp, newSet);

    pp->d_paren = stack_tos(&pp->d_paren_st)->u_size_t;
    stack_pop(&pp->d_paren_st);

    return str;
}
