#include "counter.ih"

Stack *co_sp(HashItem *item, bool errOnFailure)
{
    Stack *sp;

    if (item == PFAILED)
    {
        if (errOnFailure)
            if (message_show(MSG_ERR))
                message("Missing counter stack");
        return PFAILED;
    }

    if (stack_size(sp = (Stack *)hashitem_value(item)))
        return sp;

    if (errOnFailure)
        if (message_show(MSG_ERR))
            message("No stacked value for counter `%s'", hashitem_key(item));

    return PFAILED;
}
