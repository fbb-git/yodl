#include "yodlpost.h"

/*
    Example of a newfile entry:

        431 newfile <optional arguments>

    Marks the location of then next file to be processed.
    The file number is incremented at each construct_newfile() call, which
    is then used as the filenumber of subsequent labels. Later, when the queue
    is processed, the filecount is reset to 0. As the newfile handlers also
    increment the filecount the numbers are synchronized, and need not be kept
    inside the HashItem's value.
*/

HashItem *construct_newfile(char const *key, char *rest)
{
    global.d_filecount++;

    if (global.d_noext)
    {
        string_format(&global.d_outName, "%s%02u.%s",
                            global.d_noext,
                            (unsigned)global.d_filecount,
                            global.d_ext);
    }

                            /* arguments are for the handlers to process    */
    return *rest ?
                hashitem_construct(VOIDPTR, "", new_str(rest), free)
            :
                hashitem_construct(VOIDPTR, "", 0, root_nop);
}


