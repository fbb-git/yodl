#include "new.ih"

int *new_int(int value)
{
    int *ret = n_malloc(sizeof(int));
    *ret = value;

    return ret;
}
