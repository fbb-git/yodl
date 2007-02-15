#include "yodlpost.h"

void handle_solvelink(long offset, HashItem *item)
{
    LabelInfo *lp;
    char const *label = hashitem_key(item);
                                    /* look up the label    */
    HashItem *info = hashmap_find(&symtab, label, ANY);

    file_copy2offset(global.d_out, postqueue_istream(), offset);

    if (info == PFAILED)
    {
        message_show(MSG_WARNING);
        message("Unresolved label: %s", label);
        fputs("??", global.d_out);
        return;
    }

    lp = (LabelInfo *)hashitem_value(info);

    if (lp->d_filenr)
    {
        fprintf(global.d_out, "%s%02u.%s#%s",
                    global.d_noext,
                    (unsigned)lp->d_filenr,
                    global.d_ext,
                    label);
    }
    else
    {
        fprintf(global.d_out, "%s.%s#%s",
                    global.d_noext,
                    global.d_ext,
                    label);
    }

}
