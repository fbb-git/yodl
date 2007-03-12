#include "parser.ih"

void p_parlist_symbol(register Parser *pp, bool plusPrefix, SymbolType mask)
{
    register HashItem *item = hashmap_find(&symtab, p_matched(pp), mask);

    if (hashitem_fullType(item) & (~ANY & NOEXPAND_EXEC))
        builtin_call((Builtin *)hashitem_value(item));
    else
    {
        if (plusPrefix)
            (*pp->d_insert)(pp, "+");

        (*pp->d_insert)(pp, p_matched(pp));
    }
}
