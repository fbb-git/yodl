#include "parser.ih"

void parser_dec_ws_level(register Parser *pp)
{
    p_set_ws_level(pp, --pp->d_ws_level);
}
