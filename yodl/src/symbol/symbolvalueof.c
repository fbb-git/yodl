#include "symbol.ih"

char const *symbol_valueOf(HashItem *item)
{
    Stack *sp = sy_sp(item, false);

    return sp != PFAILED ? (char const *)stack_tos(sp) : "";
}
