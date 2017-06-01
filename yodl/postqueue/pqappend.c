#include "postqueue.ih"

void  pq_append(long offset, HashItem *item,
                            void (*handler)(long offset, HashItem *))
{
    register QueueItem *qp = new_memory(1, sizeof(QueueItem));

    qp->d_offset  = offset;
    qp->d_item    = item;
    qp->d_handler = handler;

    if (postQueue.d_length == postQueue.d_size)             /* no more room */
    {
        new_size(&postQueue.d_queue, postQueue.d_size + BLOCK_QUEUEINC,
                                     postQueue.d_size, sizeof(QueueItem *));
        postQueue.d_size += BLOCK_QUEUEINC;
    }

    postQueue.d_queue[postQueue.d_length++] = qp;
}
