#include "queue.ih"

void queue_construct(register Queue *qp, char const *str)
{
    size_t used       = strlen(str);
    size_t allocated  = used + BLOCK_QUEUE;

    memcpy
    (
        qp->d_memory = qp->d_memory_end = qp->d_read = qp->d_write =
                       new_memory(allocated, sizeof(char)),
        str,
        used
    );

    qp->d_write += used;
    qp->d_memory_end += allocated;
}
