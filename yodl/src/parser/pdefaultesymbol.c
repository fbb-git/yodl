#include "parser.ih"

void p_default_symbol(register Parser *pp, bool plusPrefix,
                        SymbolType notUsed)
{
    register HashItem *item =
        hashmap_find(pp->d_symtab_ptr, p_matched(pp), BUILTIN | MACRO);

    switch (hashitem_type(item))
    {
        case BUILTIN:
            if (message_show(MSG_INFO))
                message("Calling builtin %s", p_matched(pp));
            builtin_call((Builtin *)hashitem_value(item));
        return;

        case MACRO:
            if (message_show(MSG_INFO))
                message("Expanding macro %s", p_matched(pp));
            p_expand_macro(pp, item);
        return;

        default:
            if (plusPrefix)
                (*pp->d_insert)(pp, "+");

            if (message_show(MSG_INFO))
                message("Inserting text %s", p_matched(pp));
            (*pp->d_insert)(pp, p_matched(pp));

            if (pp->d_show_nomacros)
                p_no_user_macro(pp);
        return;
    }
}
