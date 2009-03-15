#include "yodlpost.h"

void handle_xml_newfile(long offset, HashItem *item)
{
    handle_xml_done(offset, item);

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

    file_append(global.d_out, hashmap_textOf(&global.d_symbol,
                                                        "XXarticleBegin"));

    fputs(hashmap_textOf(&global.d_symbol, "title"), global.d_out);

    file_append(global.d_out, hashmap_textOf(&global.d_symbol,
                                                        "XXarticleEndTitle"));
    file_append(global.d_out, hashmap_textOf(&global.d_symbol,
                                                        "XXxhtmlBegin"));

    xml_chapterlinks((int)global.d_fileNr); /* and the chapterlinks         */
}
