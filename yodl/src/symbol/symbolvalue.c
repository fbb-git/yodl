#include "symbol.ih"

char const *symbol_value(HashItem *item)
{
    Stack *sp = sy_sp(item, true);

    return sp != PFAILED ? (char const *)stack_tos(sp) : NULL;
}
