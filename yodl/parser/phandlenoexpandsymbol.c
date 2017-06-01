#include "parser.ih"

bool p_handle_noexpand_symbol(register Parser *pp)
{
    p_parlist_symbol(pp, false, NOEXPAND_EXEC);

    return true;
}
