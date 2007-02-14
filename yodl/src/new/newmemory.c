#include "new.ih"

void *new_memory(size_t nElements, size_t sizeofElement)
{
    return n_malloc(nElements * sizeofElement);
}
