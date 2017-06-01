#include "stack.ih"

void stack_construct(register Stack *sp, void (*destructor)(void *))
{
    memset(sp, 0, sizeof(Stack));
    sp->d_size = STACK_BLOCK;
    sp->d_value = new_memory(STACK_BLOCK, sizeof(void *));
    sp->d_destructor = destructor != 0 ? destructor : st_nop;
}
