#include "yodlpost.h"

extern int args_data;
extern int postqueue_data;
extern int message_data;

int main (int argc, char **argv)
{
    char const *doctype;
    char const **ptr;

    args_data = postqueue_data = message_data;

    message_construct(argv[0]);
    args_construct(argc, argv, "?x:l:", 0);

    hashmap_construct(&symtab);
    lines_construct(&global.d_toc);
    lines_construct(&global.d_section);
    lines_add(&global.d_section, "");

    hashmap_constructText(&global.d_symbol, default_symbols);

    if (!args_ok() || args_nArgs() < 2)     /* check arguments */
        usage();

    if (args_nArgs() == 2)                  /* file name specified  */
    {
        global.d_out = stdout;
        global.d_noext = 0;
    }
    else
    {
        global.d_noext = file_rmExtension(args_arg(2));
        global.d_ext = file_extension(args_arg(2));
        if (!global.d_ext)
        {
            global.d_ext = new_str(args_optarg('x'));
            if (!global.d_ext)
                global.d_ext = "ypp";      /* Yodl Post Processor  */
        }
    }

    string_construct(&global.d_outName, 0);
    postqueue_construct(task);

    if (global.d_noext)
    {
        string_format(&global.d_outName, "%s.%s",
                            global.d_noext, global.d_ext);

        global.d_out = file_open(string_str(&global.d_outName), "w");
    }

    doctypes[sizeofDocType - 1] =
                    doctype = hashmap_textOf(&global.d_symbol, "documenttype");

    for
    (
        ptr = doctypes, global.d_doctype = 1;
            strcmp(doctype, *ptr);
                ptr++, global.d_doctype <<= 1
    )
        ;

    postqueue_process();

    fclose(global.d_out);
    return 0;
}
