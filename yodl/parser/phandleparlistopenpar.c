#include "parser.ih"

bool p_handle_parlist_openpar(register Parser *pp)
{
    if (pp->d_paren++)              /* only insert 2nd, 3rd etc. openparams */
        (*pp->d_insert)(pp, "(");

    return true;
}
