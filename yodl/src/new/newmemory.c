#include "new.ih"

void *new_memory(unsigned nElements, unsigned sizeofElement)
{
    return n_malloc(nElements * sizeofElement);
}
