#include "counter.ih"

int counter_value(HashItem *item)
{
    Stack *sp = co_sp(item, true);

    return sp == PFAILED ? 0 : (int)stack_tos(sp);
}
