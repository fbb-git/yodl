#include "queue.ih"

void queue_unget(register Queue *qp, int ch)
{
    if (qp->d_read == qp->d_memory)         /* wrap to the end of the   */
        qp->d_read = qp->d_memory_end;      /* buffer if at the begin   */

    *--qp->d_read = ch;                     /* reset head, store char   */
}
