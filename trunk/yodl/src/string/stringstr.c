#include "string.ih"

char const *string_str(register String const *sp)
{
    return sp->d_str;
}
