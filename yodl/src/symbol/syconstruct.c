#include "symbol.ih"

Stack *sy_construct(char const *value)
{
    register StackValue stValue;

    Stack *stack = (Stack *)new_memory(1, sizeof(Stack));

    stack_construct(stack, free);

    stValue.u_charp = new_str(value);
    stack_push(stack, stValue);

    return stack;
}
