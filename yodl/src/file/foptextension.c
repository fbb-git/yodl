#include "file.ih"

/*
    if name has a .yo extension by itself or if a file {name}.yo exists, then
    use that file. Otherwise report failure
*/

Result f_opt_extension(String *name)
{
    register char const *ext = f_dotExtension(string_str(name));

    if 
    (
        ext &&
        strcmp(ext, DEFAULT_EXT) == 0
        &&
        f_isReadable(name)
    )
        return SUCCESS;                 /*  name is already readable */

    string_addstr(name, DEFAULT_EXT);   /* try our default extension */

    return f_isReadable(name) ? SUCCESS : FAILED;
}
