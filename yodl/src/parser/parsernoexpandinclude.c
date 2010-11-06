#include "parser.ih"

void parser_noexpand_include(register Parser *pp, char const *filename,
                                bool searchPath)
{
    char *pathname =
            searchPath ?
                file_fullpath(pp->d_symtab_ptr, filename)
            :
                new_str(filename);

//fprintf(stderr, "In %s: looking for %s\n", new_getcwd(), pathname);

    if (access(pathname, R_OK) != 0)
    {
        if (message_show(MSG_ERR))
            message("%s: Can't find `%s'", parser_fun(), filename);
    }
    else
    {
        FILE *f;
        register char *buffer;

        if (message_show(MSG_NOTICE))
            message("%s `%s'", parser_fun(), pathname);

        f = file_open(pathname, "r");
        buffer = new_memory(MAX_LINE_LENGTH, sizeof(char));

        while (fgets (buffer, MAX_LINE_LENGTH, f))
            (*pp->d_insert)(pp, buffer);

        fclose(f);
        free(buffer);
        if (message_show(MSG_INFO))
            message("%s `%s' included", parser_fun(), pathname);
    }

    if (searchPath)
        free(pathname);
}
