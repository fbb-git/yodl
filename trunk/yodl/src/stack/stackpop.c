#include "stack.ih"

void stack_pop(register Stack *sp)
{
    if (!sp->d_n)
        if (message_show(MSG_EMERG))
            message("Stack underflow of stack %p", sp);

    (*sp->d_destructor)(sp->d_value[--sp->d_n].u_voidp);
}
