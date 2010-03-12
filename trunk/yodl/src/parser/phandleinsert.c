#include "parser.ih"

bool p_handle_insert(register Parser *pp)
{
    (*pp->d_insert)(pp, lexer_text(&pp->d_lexer));

    return true;
}
