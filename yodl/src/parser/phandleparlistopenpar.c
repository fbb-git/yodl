#include "parser.ih"

bool p_handle_parlist_openpar(register Parser *pp)
{
    if (pp->d_paren++)              /* only insert 2nd, 3rd etc. openparams */
        (*pp->d_insert)(pp, "(");

    return true;
}

bool p_handle_collect_openpar(register Parser *pp)
{
    if (pp->d_paren == 0)
        lexer_setSubst(&pp->d_lexer, pp->d_emptySubst);

    return p_handle_parlist_openpar(pp);
}

