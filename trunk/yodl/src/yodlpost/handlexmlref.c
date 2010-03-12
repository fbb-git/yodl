#include "yodlpost.h"

void handle_xml_ref(long offset, HashItem *item)
{
    LabelInfo *lp;
    char const *documentbase;
    char const *label = hashitem_key(item);
    register char *xml_label;

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
    documentbase = hashmap_textOf(&global.d_symbol, "XXdocumentbase");

    xml_label = xml_label_name(label);

    if (lp->d_filenr)
    {
        fprintf(global.d_out,
            "<a href=\"%s%s%02u#%s\">%s</a>",
            documentbase,
            global.d_noext, (unsigned)lp->d_filenr,
            xml_label,
            lines_at(&global.d_section, lp->d_section));
    }
    else
    {
        fprintf(global.d_out,
            "<a href=\"%s%s#%s\">%s</a>",
            documentbase,
            global.d_noext,
            xml_label,
            lines_at(&global.d_section, lp->d_section));
    }

    free(xml_label);
}
