#include "yodlpost.h"

void handle_xml_label(long offset, HashItem *item)
{
    register char *label;

    file_copy2offset(global.d_out, postqueue_istream(), offset);

    label = xml_label_name(hashitem_key(item));
    fprintf(global.d_out, "<a id=\"%s\"></a>", label);
    free (label);
}
