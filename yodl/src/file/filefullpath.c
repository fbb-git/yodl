#include "file.ih"

char *file_fullpath(HashMap *symtab, char const *filename)
{
    String fname;
    char const *includePath;

    if (message_show(MSG_NOTICE))
        message("Looking for file `%s'", filename);
    string_construct(&fname, filename);
    includePath = file_includePath(symtab);

    return
        *filename == '/' || !includePath ?          /* absolute path, or no */
            f_as_is(filename, &fname)               /* include path         */
        :
            f_search_path(filename, &fname,         /* or search the path   */
                                    includePath);
}
