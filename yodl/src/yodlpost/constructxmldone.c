#include "yodlpost.h"

/*
    Example of a newfile entry:

        431 xmldone <p-level>

*/

HashItem *construct_xml_done(char const *key, char *rest)
{
    return hashitem_new_destructor(VOIDPTR, "", new_str(rest), free);
}
