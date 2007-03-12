#include "counter.ih"

void counter_set(HashItem *item, int value)
{
    Stack *sp = co_sp(item, true);

    if (sp != PFAILED)
    {
        register StackValue stValue;
        stValue.u_int = value;
        stack_assign(sp, stValue);
    }
}
