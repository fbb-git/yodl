#include "yodlpost.h"

/*
    A `labvalue label' command gets its label name stored as the key, and its
    offset as its value.
*/

HashItem *construct_labvalue(char const *key, char *rest)
{
    if (*rest)
        return hashitem_construct(VOIDPTR, rest, 0, root_nop);

    message_error("Missing label name at `labelname' entry");
    return 0;
}
