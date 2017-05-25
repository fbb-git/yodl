#include "parser.ih"

bool p_handle_parlist_closepar(register Parser *pp)
{
    if (!--pp->d_paren)
        return false;

    (*pp->d_insert)(pp, ")");
    return true;
}


bool p_handle_collect_closepar(register Parser *pp)
{
    bool ret =p_handle_parlist_closepar(pp);

    if (pp->d_paren == 0)
        lexer_setSubst(&pp->d_lexer, pp->d_subst);

    return ret;
}
