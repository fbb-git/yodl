#include "yodlpost.h"

/*
    Labvalue inserts the sectionname of a label into the current output file
    at the indicated offset. Nothing is freed, as the section names are
    shared.
*/

void handle_labvalue(long offset, HashItem *item)
{
    HashItem *info = hashmap_find(&symtab, hashitem_key(item), ANY);

    file_copy2offset(global.d_out, postqueue_istream(), offset);

    if (info != PFAILED)                            /* write its section    */
    {
        LabelInfo *li = (LabelInfo *)hashitem_value(info);
        fputs(lines_at(&global.d_section, li->d_section), global.d_out);
    }
    else
    {
        warning("Unresolved label: %s", hashitem_key(item));
        fputs("??", global.d_out);
    }
}
