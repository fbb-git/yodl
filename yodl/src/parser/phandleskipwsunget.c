#include "parser.ih"

bool p_handle_skipws_unget(register Parser *pp)
{
    lexer_unget_matched(&pp->d_lexer);
    return false;
}
