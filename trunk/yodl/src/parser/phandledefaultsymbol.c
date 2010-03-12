#include "parser.ih"

bool p_handle_default_symbol(register Parser *pp)
{
    p_default_symbol(pp, false, 0);
    return true;
}
