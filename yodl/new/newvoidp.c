#include "new.ih"

void *new_voidp(void *value)        /* returns pointer to value */
{
    void **ret = n_malloc(sizeof(void *));
    *ret = value;

    return (void *)ret;
}
