#include "new.ih"

void  *new_size(void *memory, unsigned new, unsigned old,
                                            unsigned sizeofElement)
{
    void *ret =
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
