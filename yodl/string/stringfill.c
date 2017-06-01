#include "string.ih"

void string_fill(register String *s, size_t length, int fill)
{
    s_size(s, length);

    memset(s->d_str, fill, length);
    s->d_str[length] = 0;
    s->d_length = length;
}
