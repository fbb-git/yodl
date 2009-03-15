#include "yodlpost.h"

void handle_html_label(long offset, HashItem *item)
{
    file_copy2offset(global.d_out, postqueue_istream(), offset);

    fprintf(global.d_out, "<a name=\"%s\"></a>", hashitem_key(item));
}
