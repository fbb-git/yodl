#include "counter.ih"

void counter_add(HashItem *item, int value)
{
    Stack *sp = co_sp(item, true);

    if (sp != PFAILED)
        stack_assign(sp, (void *)((int)stack_tos(sp) + value));
}
