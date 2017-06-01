#include "symbol.ih"

Stack *sy_sp(HashItem *item, bool errOnFailure)
{
    Stack *sp;

    if (item == PFAILED)
    {
        if (errOnFailure)
            if (message_show(MSG_ERR))
                message("Missing symbol stack");
        return PFAILED;
    }

    if (stack_size(sp = (Stack *)hashitem_value(item)))
        return sp;

    if (errOnFailure)
        if (message_show(MSG_ERR))
            message("No stacked value for symbol `%s'", hashitem_key(item));

    return PFAILED;
}
