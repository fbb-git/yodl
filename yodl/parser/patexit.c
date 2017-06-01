#include "parser.ih"

bool p_atexit(register Parser *pp)
{
    register char const *tos;

    if (!stack_size(&pp->d_atexit_st))
        return false;

    tos = stack_tos(&pp->d_atexit_st)->u_charCp;

    if (message_show(MSG_INFO | MSG_DEBUG))
        message("Pushing ATEXIT string `%s'", string_short(tos));

    lexer_push_str(&pp->d_lexer, tos);
    stack_pop(&pp->d_atexit_st);

    return true;
}
