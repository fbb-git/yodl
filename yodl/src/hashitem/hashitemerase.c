#include "hashitem.ih"

void hashitem_delete(register HashItem **item)
{
    (*(*item)->d_destructor)((*item)->d_value);
    free((*item)->d_key);
    free(*item);
    *item = 0;
}
