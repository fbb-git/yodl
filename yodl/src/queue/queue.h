#ifndef INCLUDED_QUEUE_H_
#define INCLUDED_QUEUE_H_

#include "../root/root.h"

typedef struct
{
    char *d_memory;
    char *d_memory_end;
    char *d_read;
    char *d_write;
}
Queue;

void queue_construct(register Queue *qp, char const *str);
int queue_get(register Queue *qp);
void queue_push(register Queue *qp, size_t extra_length, char const *info);
void queue_unget(register Queue *qp, int ch);           /* must have room   */

/* 
    Internal use only. Not used outside of this directory, needed here
    to allow proper compilation of the static inline functions below
*/

#include <stdlib.h>
#include <stdio.h>


/*  public interface continues from here */


static inline int queue_peek(register Queue *qp)
{
    return qp->d_read != qp->d_write ? *qp->d_read : EOF;
}
static inline void queue_destructor(register Queue *qp)
{
    free(qp->d_memory);
}

#endif
