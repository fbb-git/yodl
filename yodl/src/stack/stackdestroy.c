#include "stack.ih"

void stack_destroy(void *sp)
{
    unsigned idx = ((Stack *)sp)->d_n;
    register void **stack = ((Stack *)sp)->d_value;

    for ( ; idx--; stack++)
        (*((Stack *)sp)->d_destructor)(*stack);

    free(((Stack *)sp)->d_value);
}
