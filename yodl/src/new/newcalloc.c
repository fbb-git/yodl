#include "new.ih"

void *new_calloc(unsigned nElements, unsigned sizeofElement)
{
    nElements *= sizeofElement;
    return memset(n_malloc(nElements), 0, nElements);
}
