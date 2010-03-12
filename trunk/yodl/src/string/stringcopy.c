#include "string.ih"

void string_copy(register String *dest, String *src)
{
    free(dest->d_str);
    s_init(dest, src->d_str);
}
