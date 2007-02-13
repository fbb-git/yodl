#include "stack.ih"

void stack_destroy(void *sp)
{
    unsigned idx = ((Stack *)sp)->d_n;
    register StackValue *stack = ((Stack *)sp)->d_value;

    for ( ; idx--; stack++)
        (*((Stack *)sp)->d_destructor)(stack->u_voidp);

    free(((Stack *)sp)->d_value);
}
