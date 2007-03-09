#include "yodlpost.h"

/*
    Example of a verb entry:

        431 verb on

    Indicates that ignorews requests should be ignored (so, ws should be KEPT)

    The comparison (*(rest + 1) == 'n') evaluates to 1 (true) at `on', and to
        0 (false) at `off'.
*/

HashItem *construct_verb(char const *key, char *rest)
{
    return hashitem_construct(VOIDPTR, "",
                    (void *)(size_t)(*(rest + 1) == 'n'), root_nop);
}
