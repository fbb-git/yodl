#include "yodlpost.h"

void handle_html_newfile(long offset, HashItem *item)
{
    char const *cp;
    size_t nStyleOpts;

    handle_html_done(offset, item);

    if (global.d_noext)
    {
        fclose(global.d_out);
                                            /* construct the new output     */
                                            /* file name                    */
        string_format(&global.d_outName, "%s%02u.%s",
                            global.d_noext,
                            (unsigned)global.d_fileNr,
                            global.d_ext);

                                            /* and open it                  */
        global.d_out = file_open(string_str(&global.d_outName), "w");
    }

                                           /* Next, write the header       */
    if (global.d_html5)
        fputs("<!DOCTYPE html>", global.d_out);

    fputs("<html><head>\n", global.d_out);

    cp = hashmap_textOf(&global.d_symbol, "metacharset");

    if (strlen(cp) != 0)
        fprintf(global.d_out, "<meta charset=\"%s\">\n", cp);

    fprintf
    (
        global.d_out,
        "<title> %s </title>\n"
        "%s",
            hashmap_textOf(&global.d_symbol, "title"),
            hashmap_textOf(&global.d_symbol, "headopt")
    );

    if ((nStyleOpts = lines_size(&global.d_styleopt)) != 0)
    {
        size_t idx;

        fputs("<style type=\"text/css\">\n", global.d_out);
        for (idx = 0; idx != nStyleOpts; ++idx)
            fprintf(global.d_out, "    %s\n", 
                                  lines_at(&global.d_styleopt, idx));
        fputs("</style>\n", global.d_out);
    }

    cp = hashmap_textOf(&global.d_symbol, "headfile");
    if (strlen(cp) != 0)
        file_append(global.d_out, cp);

    fprintf 
    (
        global.d_out,
        "%s"
        "</head>\n"
        "<body %s>\n",
            hashmap_textOf(&global.d_symbol, "headopt"),
            hashmap_textOf(&global.d_symbol, "bodytagopt")
    );

    html_chapterlinks((int)global.d_fileNr);    /* and the chapterlinks     */
}
