#include "string.ih"

char *string_substr(String const *sp, size_t offset, size_t length)
{
    if (sp->d_length <= offset)
        return new_str("");

    register char *cp = new_str(sp->d_str + offset);
    if (strlen(cp) > length)
        cp[length] = 0;

    return cp;
}
