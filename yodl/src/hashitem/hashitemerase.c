#include "hashitem.ih"

void hashitem_erase(register HashItem *item)
{
    (*item->d_destructor)(item->d_value);
    free(item->d_key);
}
