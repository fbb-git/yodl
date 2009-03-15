#include "symbol.ih"

char const *symbol_value(HashItem *item)
{
    Stack *sp = sy_sp(item, true);

    return sp != PFAILED ? stack_tos(sp)->u_charCp : NULL;
}
