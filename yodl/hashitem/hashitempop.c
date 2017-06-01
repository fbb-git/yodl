#include "hashitem.ih"

Result hashitem_pop(register HashItem *item)
{
    register Stack *sp;

    if (item == PFAILED)
        return FAILED;

    sp = (Stack *)hashitem_value(item);

    if (!stack_size(sp))
        return FAILED;

    stack_pop(sp);
    return SUCCESS;
}
