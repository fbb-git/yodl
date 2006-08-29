#ifndef _INCLUDED_NEW_H_
#define _INCLUDED_NEW_H_

/*
    Since this header declares the basic allocation functions, it includes for
convenience sake the header stdlib.h
*/

#include <stdlib.h>

#include "../root/root.h"

/*
    char        *new_str(char const *str);  is in root.h
*/

void        *new_memory(unsigned nElements, unsigned sizeofElement);
void        *new_calloc(unsigned nElements, unsigned sizeofElement);
int         *new_int(int value);
long        *new_long(long value);
void        *new_memory(unsigned nelements, unsigned sizeofElement);
unsigned    *new_unsigned(unsigned value);

                        /* `memory' must be the address of a pointer.
                            E.g., char *str -> new_size(&str, ...
                        */
void        *new_size(void *memory, unsigned new_n, unsigned old_n,
                                                unsigned sizeofElement);
void        *new_voidp(void *value);            /* returns pointer to value */

#endif
