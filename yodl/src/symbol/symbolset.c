#include "symbol.ih"

/*
    The symbol to add may be:
        - plain text
*/

void symbol_set(HashItem *item, char const *text)
{
    Stack *sp = sy_sp(item, true);

    if (sp != PFAILED)
        stack_assign(sp, new_str(text));
}
