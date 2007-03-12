#include "yodlpost.h"

void handle_html_done(long offset, HashItem *item)
{
    file_copy2offset(global.d_out, postqueue_istream(), offset);

    html_chapterlinks((int)global.d_fileNr++);
    fprintf(global.d_out,
            "</body>\n"
            "</html>\n");
}
