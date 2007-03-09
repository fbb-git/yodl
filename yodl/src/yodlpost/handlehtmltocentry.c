#include "yodlpost.h"

void handle_html_tocentry(long offset, HashItem *item)
{
    file_copy2offset(global.d_out, postqueue_istream(), offset);
    fprintf(global.d_out, "<a name=\"l%u\"></a>\n", 
                            (unsigned)(size_t)hashitem_value(item));
}
