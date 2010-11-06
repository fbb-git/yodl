#include "parser.ih"

void parser_process(register Parser *pp)
{
    register size_t idx;
    char const *preload;

            /* put all files in reversed order on the lexer's filestack, so */
            /* they will be processed in their reversed order, i.e., in the */
            /* order they were specified on the cmd line                    */

    if (message_show(MSG_DEBUG)) message("Number of args `%u'", 
                                         (unsigned)args_nArgs());

    for (idx = args_nArgs(); idx--; )
    {
        char const *filename = args_arg(idx);
        char *full = file_fullpath(pp->d_symtab_ptr, filename);

        if (!full && strcmp(filename, "-"))
            if (message_show(MSG_EMERG))
                message("Can't read `%s' (cwd: %s, XXincludePath: %s)", 
                        filename, new_getcwd(), 
                        file_includePath(pp->d_symtab_ptr));

        if (message_show(MSG_INFO))
            message("Stacking  `%s' for processing", filename);

        lexer_push_file(&pp->d_lexer, full);
        free(full);
    }

    preload = args_optarg('p');
    if (preload)
        lexer_push_str(&pp->d_lexer, preload);

    do
    {
        p_parse(pp);
    }
    while (p_atexit(pp));

    if (message_errors())
    {
        message("Error(s) detected");
        ostream_destroy(pp->d_outs_ptr);
        if (pp->d_indexName)
        {
            fclose(pp->d_indexFile);
            unlink(pp->d_indexName);
        }
    }
    else if (message_show(MSG_NOTICE))
        message("Parsing completed");
}
