#include "stack.ih"

size_t stack_size(Stack const *sp)
{
    return sp->d_n;
}
