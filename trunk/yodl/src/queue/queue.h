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
void queue_destructor(register Queue *qp);
int queue_get(register Queue *qp);
int queue_peek(register Queue *qp);
void queue_push(register Queue *qp, size_t extra_length, char const *info);
void queue_unget(register Queue *qp, int ch);           /* must have room   */


#endif
