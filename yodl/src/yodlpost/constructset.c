#include "yodlpost.h"

/*
    An example of the `set' index item is:

        1234 set title This is the title of the document

    title is stored as key, and what's beyond is stored as the value in
the returned HashItem structure. The handler may store these values in a
storage. The value is NOT freed after handling.

*/


HashItem *construct_set(char const *setkey, char *rest)
{
    char *key;
    HashItem *ret;

    if (!(key = string_firstword(&rest)))               /* get the key      */
    {
        message_error("`set ...: missing key");
        return 0;
    }

    if (!*string_strip(&rest))
        warning("Empty value of symbol `%s'", key);

    ret = hashitem_construct(VOIDPTR, key, new_str(rest), root_nop);
    free(key);

    return ret;
}
