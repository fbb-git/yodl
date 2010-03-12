#include "hashitem.ih"

void *hashitem_value(register HashItem *item)
{
    return item != PFAILED ? item->d_value : PFAILED;
}
