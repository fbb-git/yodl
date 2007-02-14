#include "string.ih"

size_t string_length(register String const *sp)
{
    return sp->d_length;
}
