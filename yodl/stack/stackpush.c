#include "stack.ih"

Result stack_push(register Stack *sp, register StackValue element)
{
    register size_t last = sp->d_n++;

    if (last == sp->d_size)
        new_size(&sp->d_value, sp->d_size += STACK_BLOCK,
                               last, sizeof(StackValue));

    sp->d_value[last] = element;

    return SUCCESS;
}
