#include "counter.ih"

bool counter_has_value(int *valuePtr, HashItem *item)
{
    Stack *sp = (Stack *)hashitem_value(item);

    if (sp == PFAILED || !stack_size(sp))
        return false;

    *valuePtr = (int)stack_tos(sp);

    return true;
}
