#include "yodlpost.h"

/*
    Example of a ref:

    1234 ref LabelName

    The offset and the labelname are stored in the returned HashItem.
*/

HashItem *construct_ref(char const *key, char *rest)
{
    rest = strtok(rest, " \t");

    if (rest)
        return hashitem_construct(VOIDPTR, rest, 0, root_nop);

    return 0;
}
