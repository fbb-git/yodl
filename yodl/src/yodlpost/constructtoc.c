#include "yodlpost.h"

HashItem *construct_toc(char const *key, char *rest)
{
    char *newheader = new_str(rest);
    register HashItem *item = hashmap_find(&global.d_symbol, "tocheader",
                                                             ANY);
    if (item != PFAILED)
        hashitem_set(item, newheader, free);    /* reassign existing value  */
    else                                        /* of insert new element    */
        hashmap_insert(&global.d_symbol,
             hashitem_construct(VOIDPTR, "tocheader", newheader, free));


    return hashitem_construct(VOIDPTR, rest, 0, root_nop);
}
