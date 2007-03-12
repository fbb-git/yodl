#include "yodlpost.h"

/*
    toc entries are of the form:
        tocentry sectionnumber entrytext
    e.g.,
        24121 tocentry 2.3.2: Compiling a C program by a C++ compiler

    This toc entry is eventually simply written to the output file.

*/

HashItem *construct_txt_tocentry(char const *key, char *rest)
{
    lines_add(&global.d_toc, rest);         /* add a new entry              */

    return hashitem_construct(VOIDPTR, "", 0, root_nop);
}
