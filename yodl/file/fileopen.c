#include "file.ih"

FILE *file_open(char const *name, char const *mode)
{
    FILE *file;

    if (!strcmp (name, "-"))                        /* stdin/out? */
        return *mode == 'r' ? stdin : stdout;

    if (!(file = fopen(name, mode)))
        if (message_show(MSG_CRIT))
            message("Can't %s `%s'", *mode == 'r' ? "read" : "write", name);

    return file;
}
