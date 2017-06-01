#include "yodlpost.h"

void html_chapterlinks(int current)     /* set links to next/prev chap  */
{                                       /* and table of contents        */
    if
    (
        !(global.d_doctype & (BOOK | REPORT))
        ||
        !current
    )
        return;                     /* links only in books, reports,    */
                                    /* and outside of toc itself        */
    fputs
    (
        "<hr>\n"                    /* borders the contents             */
        "<ul>\n",
        global.d_out
    );

    fprintf
    (
        global.d_out,
        "    <li> <a href=\"%s.%s\">%s</a>\n",
            global.d_noext,
            global.d_ext,
            hashmap_textOf(&global.d_symbol, "tocheader")
    );

    if (current > 1)
    {
        fprintf
        (
            global.d_out,
            "    <li> <a href=\"%s%02d.%s\">%s</a>\n",
                global.d_noext,
                current - 1,
                global.d_ext,
                hashmap_textOf(&global.d_symbol, "previous")
        );
    }

    if ((size_t)current < global.d_filecount)
    {
        fprintf
        (
            global.d_out,
            "    <li> <a href=\"%s%02d.%s\">%s</a>\n",
                global.d_noext,
                current + 1,
                global.d_ext,
                hashmap_textOf(&global.d_symbol, "next")
        );
    }

    fputs
    (
        "</ul>\n"
        "<hr>\n",                   /* borders the contents             */
        global.d_out
    );
}
