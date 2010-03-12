#include "file.ih"

Result f_opt_extension(String *name)
{
    if (f_isReadable(name))
        return SUCCESS;                 /*  name is already readable */

    string_addstr(name, DEFAULT_EXT);   /* try our default extension */

    return f_isReadable(name) ? SUCCESS : FAILED;
}
