#include "yodlpost.h"

char *xml_label_name(char const *lab)
{
    char *ret = new_str(lab);

    register char *cp = ret;

    while (*cp)
    {
        if (!isalnum(*cp) && !strchr("_-.", *cp))
            *cp = '.';
        cp++;
    }

    return ret;
}
