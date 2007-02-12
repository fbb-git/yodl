#include "yodlpost.h"

/*
    The key's value is inserted into the &global.d_symbol hashmap. If the
indicated value already exists, it is reassigned.

    The hashitem's value is swallowed by the hashmap.
*/

void handle_set(long offset, HashItem *item)
{
    register HashItem *mapItem;
    register char const *key = hashitem_key(item);
    char *value;

    file_copy2offset(global.d_out, postqueue_istream(), offset);

                                                /* grab the item's value    */
                                                /* since the construct_set  */
                                                /* doesn't free the value   */
                                                /* it can be used here      */
                                                /* without copying          */
    value = (char *)hashitem_value(item);

    mapItem = hashmap_find(&global.d_symbol, key, ANY);

    if (mapItem != PFAILED)
        hashitem_set(mapItem, value, free);     /* reassign existing value  */
    else                                        /* of insert new element    */
        hashmap_insert(&global.d_symbol,
                        hashitem_construct(VOIDPTR, key, value, free));
}
