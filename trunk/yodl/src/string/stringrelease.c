#include "string.ih"

/*
    returns d_str. Afther this the string is invalid, but destroy() can be
    used (as can destructor()
*/

char *string_release(register String *sp)
{
    register char *ret = sp->d_str;

    sp->d_str = 0;
    return ret;
}
