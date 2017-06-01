#include "yodlpost.h"

void handle_txt_ref(long offset, HashItem *item)
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

    fprintf(global.d_out,
            "%s",
            lines_at(&global.d_section, lp->d_section));
}
