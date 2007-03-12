#include "hashitem.ih"

void hashitem_set(register HashItem *item, void *value,
                    void (*destructor)(void *))
{
    item->d_value = value;
    item->d_destructor = destructor;
}
