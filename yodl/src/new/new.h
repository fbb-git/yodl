#ifndef INCLUDED_NEW_H_
#define INCLUDED_NEW_H_

/*
    Since this header declares the basic allocation functions, it includes for
convenience sake the header stdlib.h
*/

#include <stdlib.h>

#include "../root/root.h"

/*
    char        *new_str(char const *str);  is in root.h
*/

void        *new_memory(size_t   nElements, size_t   sizeofElement);
void        *new_calloc(size_t   nElements, size_t   sizeofElement);
int         *new_int(int value);
long        *new_long(long value);
void        *new_memory(size_t   nelements, size_t   sizeofElement);

                        /* `memory' must be the address of a pointer.
                            E.g., char *str -> new_size(&str, ...
                        */
void        *new_size(void *memory, size_t   new_n, size_t   old_n,
                                                size_t   sizeofElement);
void        *new_voidp(void *value);            /* returns pointer to value */

#endif
