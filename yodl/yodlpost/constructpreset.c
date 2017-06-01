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
    {                                                   /* e.g., title      */
        message_error("`preset ...: missing key");
        return 0;
    }

    if (strcmp(key, "nohtmlfive") == 0)
        global.d_html5 = 0;
    else
    {
        if (!*string_strip(&rest))                      /* get the value    */
            warning("Empty value of symbol `%s'", key); /* e.g., This is... */
    
        if (strcmp(key, "styleopt") == 0)               /* store styleopts  */
            lines_add(&global.d_styleopt, rest);
        else
        {                                                   
                                                        /* look up the key  */
            mapItem = hashmap_find(&global.d_symbol, key, ANY); 
    
            if (mapItem != PFAILED)                     /* reassign         */
                hashitem_set(mapItem, rest, free);      /* existing value   */
            else                                        /* or insert new    */
                hashmap_insert(&global.d_symbol,        /* element          */
                    hashitem_new_destructor(VOIDPTR, key, new_str(rest), free));
        }
    }
    free(key);
    return hashitem_new_destructor(VOIDPTR, "", 0, root_nop);
}
