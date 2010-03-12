#include "root.ih"

char *new_str(char const *s)
{
    char *ret;

    if (!(ret = strdup(!s || !*s ? "" : s)))
        out_of_memory();

    return ret;
}
