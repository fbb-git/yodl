#include "parser.ih"

void p_set_ws_level(register Parser *pp, register int value)
{
    if (value < 0)
    {
        if (message_show(MSG_WARNING))
            message("Can't reduce whitespace level below 0");
        return;
    }

    ostream_set_ws_level(pp->d_outs_ptr, (size_t)value);
    lexer_set_keep_ws(&pp->d_lexer, pp->d_keep_ws || value == 0);
}
