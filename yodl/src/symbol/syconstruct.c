#include "symbol.ih"

Stack *sy_construct(char const *value)
{
    Stack *stack = (Stack *)new_memory(1, sizeof(Stack));

    stack_construct(stack, free);
    stack_push(stack, new_str(value));

    return stack;
}
