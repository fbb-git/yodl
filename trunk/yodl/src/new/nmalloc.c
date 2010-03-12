
#include "new.ih"

void *n_malloc(size_t size)
{
    register void *mem;

    if (!size)
        return 0;

    mem = malloc(size);

    if (!mem)
        out_of_memory();

    return mem;
}
