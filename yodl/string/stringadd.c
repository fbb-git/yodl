#include "string.ih"

void string_add(register String *dest, register String *src)
{
    size_t newlength = dest->d_length + src->d_length;

    s_size(dest, newlength);

    strcpy
    (
        dest->d_str + dest->d_length,
        src->d_str
    );

    dest->d_length = newlength;
}
