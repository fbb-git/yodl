#include "parser.ih"

bool p_handle_parlist_closepar(register Parser *pp)
{
    if (!--pp->d_paren)
        return false;

    (*pp->d_insert)(pp, ")");
    return true;
}
