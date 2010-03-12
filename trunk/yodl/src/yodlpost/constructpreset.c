#include "yodlpost.h"

/*
    An example of the `preset' index item is:

        1234 preset title This is the title of the document

    title is stored immediately. No action at `handle'

*/


HashItem *construct_preset(char const *setkey, char *rest)
{
    char *key;
    HashItem *mapItem;

    if (!(key = string_firstword(&rest)))               /* get the key      */
    {
        message_error("`preset ...: missing key");
        return 0;
    }

    if (!*string_strip(&rest))                          /* get the value    */
        warning("Empty value of symbol `%s'", key);

    mapItem = hashmap_find(&global.d_symbol, key, ANY); /* look up the key  */

    if (mapItem != PFAILED)
        hashitem_set(mapItem, rest, free);      /* reassign existing value  */
    else                                        /* of insert new element    */
        hashmap_insert(&global.d_symbol,
                        hashitem_construct(VOIDPTR, key, new_str(rest), free));

    free(key);
    return hashitem_construct(VOIDPTR, "", 0, root_nop);
}
