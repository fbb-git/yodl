#include "new.ih"

unsigned *new_unsigned(unsigned value)
{
    unsigned *ret = n_malloc(sizeof(unsigned));
    *ret = value;

    return ret;
}
