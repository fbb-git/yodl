#include "postqueue.ih"

void  postqueue_process()
{
    QueueItem **begin = postQueue.d_queue;
    QueueItem **end = begin + postQueue.d_length;

    while (begin != end)
    {
        register QueueItem *item = *begin++;

        (*item->d_handler)(item->d_offset, item->d_item);

        hashitem_erase(item->d_item);
        free(item->d_item);
        free(item);
    }
}
