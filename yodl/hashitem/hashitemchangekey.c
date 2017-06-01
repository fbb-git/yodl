#include "hashitem.ih"

void hashitem_changekey(register HashItem *hashitem, char const *newkey)
{
    free(hashitem->d_key);
    hashitem->d_key = new_str(newkey);
}
