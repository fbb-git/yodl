#include "string.ih"

void string_addstr(register String *str, register char const *add)
{
    unsigned newlength;

    if (!add || !*add)
        return;

    newlength = str->d_length + strlen(add);

    s_size(str, newlength);

    strcpy(str->d_str + str->d_length, add);

    str->d_length = newlength;
}
