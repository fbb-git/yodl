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
        register StackValue stValue;

        string_construct(&value, stack_tos(sp)->u_charCp);
        string_addstr(&value, text_to_add);

        stValue.u_charp = string_release(&value); 
        stack_assign(sp, stValue);
    }
}
