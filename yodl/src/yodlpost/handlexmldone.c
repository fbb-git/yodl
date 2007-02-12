#include "yodlpost.h"

void handle_xml_done(long offset, HashItem *item)
{
    file_copy2offset(global.d_out, postqueue_istream(), offset);

    xml_chapterlinks((int)global.d_fileNr++);

    file_append(global.d_out, hashmap_textOf(&global.d_symbol,
                                                        "XXxhtmlEnd"));
    fputs("</s:mainContent>\n", global.d_out);

    file_append(global.d_out, hashmap_textOf(&global.d_symbol,
                                                        "XXarticleSummary"));
    fputs("</ga:generalArticle>\n", global.d_out);
}
