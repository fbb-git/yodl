#include "yodlpost.h"

/*
    Labels are stored in the symboltable.

    The current section number, the filecount and the sectionnumber is
    stored in the HashItem.

    Example of an index-line:

        432 label Overview

    The label name follows the `label' key, and it is stored inside
hashitem. An error occurs if the label name is not available.

*/

HashItem *construct_label(char const *key, char *rest)
{
    HashItem *item;

    LabelInfo *li = new_memory(1, sizeof(LabelInfo));
    li->d_section = lines_size(&global.d_section) - 1;
    li->d_filenr = global.d_filecount;

    if (!*rest)
    {
        message_error("Missing label name");
        return 0;
    }

    item =  hashitem_construct(VOIDPTR, rest, li, free);

    if (hashmap_insert(&symtab, item) == FAILED)
    {
        message_show(MSG_ERR);
        message("%s: %s doubly defined", args_programName(), key);
        return 0;
    }

    return hashitem_construct(VOIDPTR, rest, 0, root_nop);
}
