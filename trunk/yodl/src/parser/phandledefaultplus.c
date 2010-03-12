#include "parser.ih"

bool p_handle_default_plus(register Parser *pp)
{
    return p_plus_series(pp, p_default_symbol, 0);
}
