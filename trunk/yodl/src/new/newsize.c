#include "new.ih"

void  *new_size(register void *memory, size_t new, size_t old,
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

    free (*(void **)memory);
    return *(void **)memory = ret;
}
