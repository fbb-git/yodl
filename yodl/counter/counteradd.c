#include "counter.ih"

void counter_add(HashItem *item, int value)
{
    Stack *sp = co_sp(item, true);

    if (sp != PFAILED)
    {
        register StackValue stValue = *stack_tos(sp);
        stValue.u_int += value;

        stack_assign(sp, stValue);
    }
}
