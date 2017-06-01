#include "string.ih"

void string_swallow(String *dest, String *src)
{
    free(dest->d_str);
    dest->d_str = src->d_str;
    dest->d_length = src->d_length;
    dest->d_size = src->d_size;
}
