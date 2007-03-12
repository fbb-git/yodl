#include "string.ih"

size_t string_count(String *sp, char needle)
{
    register size_t count = 0;
    register char *cp = sp->d_str;

    while ((cp = strchr(cp, needle)))
    {
        count++;
        cp++;
    }
    return count;
}
