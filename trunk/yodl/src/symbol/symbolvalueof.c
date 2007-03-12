#include "symbol.ih"

char const *symbol_valueOf(HashItem *item)
{
    Stack *sp = sy_sp(item, false);

    return sp != PFAILED ? stack_tos(sp)->u_charCp : "";
}
