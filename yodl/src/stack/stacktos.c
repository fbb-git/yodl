#include "stack.ih"

void *stack_tos(Stack const *sp)
{
    return sp->d_n ? sp->d_value[sp->d_n - 1] : PFAILED;
}
