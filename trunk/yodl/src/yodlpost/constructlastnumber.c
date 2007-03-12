#include "yodlpost.h"

/*
    A simple key required no special handling. Any information it contains is
stored in a KeyInfo struct, containing the offset and the `rest' info.  The
stored info is then handled by specific handlers.

    The handler is responsible for freeing the information that is stored at
the d_tail field. The KeyInfo itself is freed by the postprocessor.

*/

HashItem *construct_lastnumber(char const *key, char *rest)
{
    if (!(*string_strip(&rest)))
        warning("No section specified at `lastnumber'");

    lines_add(&global.d_section, rest);     /* empty is no problem here  */
    return hashitem_construct(VOIDPTR, "", 0, root_nop);
}
