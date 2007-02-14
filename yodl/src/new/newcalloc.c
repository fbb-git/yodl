#include "new.ih"

void *new_calloc(size_t nElements, size_t sizeofElement)
{
    nElements *= sizeofElement;
    return memset(n_malloc(nElements), 0, nElements);
}
