#include "yodlpost.h"

void xml_chapterlinks(int current)     /* set links to next/prev chap  */
{                                       /* and table of contents        */
    char const *documentbase;

    if
    (
        !(global.d_doctype & (BOOK | REPORT))
        ||
        !current
    )
        return;                     /* links only in books, reports,    */
                                    /* and outside of toc itself        */

    file_append(global.d_out, hashmap_textOf(&global.d_symbol,
                                                        "XXxhtmlEnd"));
    file_append(global.d_out, hashmap_textOf(&global.d_symbol,
                                                        "XXxhtmlBegin"));

    fputs("<table><tbody>\n", global.d_out);

    documentbase = hashmap_textOf(&global.d_symbol, "XXdocumentbase");

    fprintf
    (
        global.d_out,
        "    <tr><td> <a href=\"%s%s\">%s</a></td></tr>\n",
            documentbase,
            global.d_noext,
            hashmap_textOf(&global.d_symbol, "tocheader")
    );

    if (current > 1)
        fprintf
        (
            global.d_out,
            "    <tr><td> <a href=\"%s%s%02d\">%s</a></td></tr>\n",
                documentbase,
                global.d_noext,
                current - 1,
                hashmap_textOf(&global.d_symbol, "previous")
        );

    if ((size_t)current < global.d_filecount)
        fprintf
        (
            global.d_out,
            "    <tr><td><a href=\"%s%s%02d\">%s</a></td></tr>\n",
                documentbase,
                global.d_noext,
                current + 1,
                hashmap_textOf(&global.d_symbol, "next")
        );

    fputs("</tbody></table>\n", global.d_out);
    file_append(global.d_out, hashmap_textOf(&global.d_symbol,
                                                        "XXxhtmlEnd"));
    file_append(global.d_out, hashmap_textOf(&global.d_symbol,
                                                        "XXxhtmlBegin"));

}
