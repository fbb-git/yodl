#include "file.ih"

char *file_dirname(char const *path)
{
    char *cp;
    char *ret;

    ret = new_str(dirname(cp = new_str(path)));
    free(cp);

    return ret;
}
