#include "new.ih"

long *new_long(long value)
{
    long *ret = n_malloc(sizeof(long));
    *ret = value;

    return ret;
}
