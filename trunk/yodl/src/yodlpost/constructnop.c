#include "yodlpost.h"

/*
    Nothing to do here.
*/

HashItem *construct_nop(char const *key, char *rest)
{
    return hashitem_construct(VOIDPTR, "", 0, root_nop);
}
