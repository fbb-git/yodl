#include "file.ih"

char *file_basename(char const *path)
{
    char *cp;
    char *ret;

    ret = new_str(basename(cp = new_str(path)));
    free(cp);

    return ret;
}
