#include "counter.ih"

Stack *co_construct(int value)
{
    Stack *counter = (Stack *)new_memory(1, sizeof(Stack));
    register StackValue stValue;

    stack_construct(counter, 0);        /* just values, nothing allocated   */
    stValue.u_int = value;
    stack_push(counter, stValue);

    return counter;
}
