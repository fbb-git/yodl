#include "stack.ih"

unsigned stack_size(Stack const *sp)
{
    return sp->d_n;
}
