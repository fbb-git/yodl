#include "string.ih"

void s_init(register String *str, register char const *txt)
{
    size_t newlength = strlen(txt);

    str->d_size = 0;
    str->d_str = 0;

    s_size(str, newlength);
    strcpy(str->d_str, txt);
    str->d_length = newlength;
}
