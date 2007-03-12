#include "file.ih"

bool f_isReadable(String const *name)
{
    struct stat statbuf;
    char const *nm = string_str(name);

    return
        !stat(nm, &statbuf)         /* `name' exists    */
        &&
        S_ISREG(statbuf.st_mode)    /* and is a regular file */
        &&
        access(nm, R_OK) == 0;      /* and is readable by the Yodl process */
}
