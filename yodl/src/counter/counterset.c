#include "counter.ih"

void counter_set(HashItem *item, int value)
{
    Stack *sp = co_sp(item, true);

    if (sp != PFAILED)
        stack_assign(sp, (void *)value);
}
