#include "string.ih"

unsigned string_length(register String const *sp)
{
    return sp->d_length;
}
