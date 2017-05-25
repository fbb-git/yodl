#include "parser.ih"

bool p_handle_default_symbol(register Parser *pp)
{
    if (strcmp(p_matched(pp), "verbo") == 0)
        lexer_setSubst(&pp->d_lexer, pp->d_emptySubst);

    p_default_symbol(pp, false, 0);
    return true;
}
