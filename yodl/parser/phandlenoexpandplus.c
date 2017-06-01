#include "parser.ih"

/*
    Within a no-expand parameter list, CHAR() tokens are interpreted. This
    only occurs in NOEXPAND() calls
*/

bool p_handle_noexpand_plus(register Parser *pp)
{
    register bool ret;

    ret = p_plus_series(pp, p_parlist_symbol, NOEXPAND_EXEC);
    return ret;
}
