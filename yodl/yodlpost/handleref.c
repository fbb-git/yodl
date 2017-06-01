#include "yodlpost.h"

void handle_ref(long offset, HashItem *item)
{
    LabelInfo *lp;
    char const *label = hashitem_key(item);
                                                /* look up the label    */
    HashItem *info = hashmap_find(&symtab, label, ANY);

    file_copy2offset(global.d_out, postqueue_istream(), offset);

    if (info == PFAILED)
    {
        warning("Unresolved label: %s", label);
        fputs("??", global.d_out);
        return;
    }

    lp = (LabelInfo *)hashitem_value(info);

    if (lp->d_filenr)
    {
        fprintf(global.d_out,
            "<a href=\"%s%02u.%s#%s\">%s</a>",
            global.d_noext, (unsigned)lp->d_filenr,
            global.d_ext,
            label,
            lines_at(&global.d_section, lp->d_section));
    }
    else
    {
        fprintf(global.d_out,
            "<a href=\"%s.%s#%s\">%s</a>",
            global.d_noext,
            global.d_ext,
            label,
            lines_at(&global.d_section, lp->d_section));
    }
}
