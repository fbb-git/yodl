#include "symbol.ih"

/*
    The symbol to add may be:
        - plain text
*/

void symbol_add(HashItem *item, char const *text_to_add)
{
    Stack *sp = sy_sp(item, true);

    if (sp != PFAILED)
    {
        String value;
        string_construct(&value, (char const *)stack_tos(sp));
        string_addstr(&value, text_to_add);

        stack_assign(sp, string_release(&value));
    }
}
