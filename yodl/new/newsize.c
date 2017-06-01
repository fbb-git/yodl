#include "new.ih"

    /* 
        NOTE: `memory' must be the address of a pointer pointing to the
        allocated memory. E.g., it is a char **
    */
void *new_size(register void *memory, size_t new, size_t old,
                                            size_t sizeofElement)
{
    register void *ret =
        memcpy
        (
            new_calloc(new, sizeofElement),
            *(void **)memory,
            (old > new ? new : old) * sizeofElement /* copy the smallest    */
                                                    /* available size       */
        );

    free(*(void **)memory);
    return *(void **)memory = ret;
}
