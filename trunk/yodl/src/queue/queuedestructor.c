#include "queue.ih"

void queue_destructor(register Queue *qp)
{
    free(qp->d_memory);
}
