#include "queue.ih"

int queue_peek(register Queue *qp)
{
    return qp->d_read != qp->d_write ? *qp->d_read : EOF;
}
