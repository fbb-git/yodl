#include "string.ih"

unsigned string_count(String *sp, char needle)
{
    register unsigned count = 0;
    register char *cp = sp->d_str;

    while ((cp = strchr(cp, needle)))
    {
        count++;
        cp++;
    }
    return count;
}
