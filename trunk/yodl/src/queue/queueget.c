#include "queue.ih"

int queue_get(register Queue *qp)
{
    register int ch;

    if (qp->d_read != qp->d_write)
    {
        ch = *(unsigned char *)qp->d_read++;    /* return char at head  */

        if (qp->d_read == qp->d_memory_end)     /* maybe wrap around    */
            qp->d_read = qp->d_memory;

        return ch;
    }
    if (message_show(MSG_DEBUG))
        message("End of queue at %p", qp);
    return EOF;
}
