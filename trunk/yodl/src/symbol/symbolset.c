#include "symbol.ih"

/*
    The symbol to add may be:
        - plain text
*/

void symbol_set(HashItem *item, char const *text)
{
    Stack *sp = sy_sp(item, true);

    if (sp != PFAILED)
    {
        register StackValue stValue;

        stValue.u_charp = new_str(text); 
        stack_assign(sp, stValue);
    }
}
