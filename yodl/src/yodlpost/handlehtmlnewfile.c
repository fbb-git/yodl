#include "yodlpost.h"

void handle_html_newfile(long offset, HashItem *item)
{
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

    fprintf                                 /* Next, write the header       */
    (
        global.d_out,
        "<!DOCTYPE html><html><head>\n"
        "<title> %s </title>\n"
        "%s",
            hashmap_textOf(&global.d_symbol, "title"),
            hashmap_textOf(&global.d_symbol, "headopt")
    );

    char const *style = hashmap_textOf(&global.d_symbol, "styleopt");

    if (strlen(style) != 0)
        fprintf(global.d_out, 
                "<style type=\"text/css\" %s></style>\n", 
                style);
    
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
