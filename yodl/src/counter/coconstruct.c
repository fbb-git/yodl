#include "counter.ih"

Stack *co_construct(int value)
{
    Stack *counter = (Stack *)new_memory(1, sizeof(Stack));

    stack_construct(counter, 0);        /* just values, nothing allocated   */
    stack_push(counter, (void *)value);

    return counter;
}
