#include "parser.ih"

void parser_includefile(register Parser *pp, char const *filename)
{
    register char *pathname = file_fullpath(pp->d_symtab_ptr, filename);

    if (!pathname)
    {
        char const *cp = file_includePath(pp->d_symtab_ptr);
        char const *fun = parser_fun();
        if (message_show(MSG_CRIT))
            message("[Fatal] %s `%s': Not found in `%s'",
                fun, filename, cp ? cp : "<no XXincludePath>");

    }

    lexer_push_file(&pp->d_lexer, pathname);

    free (pathname);
}
