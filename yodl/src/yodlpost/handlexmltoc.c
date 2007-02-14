#include "yodlpost.h"

void handle_xml_toc(long offset, HashItem *item)
{
    register size_t idx;
    register size_t n;
    int level;
    char *filename = new_memory(1, 250);
    char const *documentbase =
                        hashmap_textOf(&global.d_symbol, "XXdocumentbase");

    file_copy2offset(global.d_out, postqueue_istream(), offset);

    fprintf(global.d_out, "<h1>%s</h1>\n", hashitem_key(item));

    for (idx = 0, n = lines_size(&global.d_toc); idx < n; idx++)
    {
        size_t nread;
        size_t labelnr;
        char const *line = lines_at(&global.d_toc, idx);

        sscanf(line, "%d %100s %d %n", &level, filename, (int *)&labelnr, 
                                                         (int *)&nread);
        fprintf
        (
            global.d_out,
            "<a href=\"%s%s#l%d\">%s</a>"
            "<br />\n",
                documentbase,
                filename,
                labelnr,
                line + nread
        );

    }

    free(filename);
}
