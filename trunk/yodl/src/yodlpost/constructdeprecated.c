#include "yodlpost.h"

/*
    The construct_deprecated constructor simply stores the key and its rest in
the returned HashItem.

    It is used for setting things like `bodytagopt' and `documenttype', which
should rather be processed by the construct_set() constructor.

    The only modification that is required to accomplish this is to call
INTERNALINDEX(set bodytagopt ...)

*/

HashItem *construct_deprecated(char const *key, char *rest)
{
    message(
        "`INTERNALINDEX(%s ...)' is deprecated, use ...(set %s ...)",
        key, key);

    return hashitem_construct(VOIDPTR, key, new_str(rest), root_nop);
}
