#include "string.ih"

void s_size(register String *dest, register size_t newsize)
{
    if (++newsize > dest->d_size)               /* ++ to acount for ascii-Z */
    {
        newsize += STRING_BLOCK;

        new_size
        (
            &dest->d_str,
            newsize,
            dest->d_size,
            sizeof(char)
        );

        dest->d_size = newsize;
    }
}
