#include "string.ih"

size_t string_find_first_of(register String *sp, char const *accept)
{
    register char *cp = strpbrk(sp->d_str, accept);

    return !cp ? FAILED : (cp - sp->d_str);
}
