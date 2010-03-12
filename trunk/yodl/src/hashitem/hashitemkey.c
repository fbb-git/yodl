#include "hashitem.ih"

char const *hashitem_key(HashItem const *item)
{
    return item->d_key;
}
