#include "string.ih"

/*
    returns d_str. After this the String object exists and can be given 
    another string. string_free is not required.
*/

char *string_release(register String *sp)
{
    register char *ret = sp->d_str;

    sp->d_str = 0;

    return ret;
}
